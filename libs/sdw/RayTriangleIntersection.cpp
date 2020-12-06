#include "RayTriangleIntersection.h"

RayTriangleIntersection::RayTriangleIntersection() {
	_isNull = true;
}

//RayTriangleIntersection::RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle, const ObjObject &object) {
//	_intersectionPoint = point;
//	_distanceFromCamera = distance;
//	_intersectedTriangle = triangle;
//	_intersectedObject = object;
//	_isNull = false;
//}

RayTriangleIntersection::RayTriangleIntersection(ModelPoint &point, float distance, ModelTriangle &triangle, Ray &ray, float e2Ratio, float e1Ratio) {
	_intersectionPoint = point;
	_distanceFromOrigin = distance;
	_intersectedTriangle = triangle;
	_isNull = false;
    _ray = ray;
    _e2Ratio = e2Ratio;
    _e1Ratio = e1Ratio;
    _e0Ratio = 1.0 - (e2Ratio + e1Ratio);
}

Ray RayTriangleIntersection::ray() {
  return _ray;
}

bool RayTriangleIntersection::isNull() {
	return _isNull;
}

float RayTriangleIntersection::getDistanceFromOrigin() {
	return _distanceFromOrigin;
}

ModelPoint RayTriangleIntersection::getIntersectionPoint() {
	return _intersectionPoint;
}

glm::vec3 RayTriangleIntersection::normal() {
  if(!_intersectedTriangle.v0().hasVertexNormal()) {
    return _intersectedTriangle.normal();
  }
  glm::vec3 normal = _e0Ratio * _intersectedTriangle.v0().normal() +
                      _e2Ratio * _intersectedTriangle.v1().normal() +
                      _e1Ratio * _intersectedTriangle.v2().normal();
  return normal;
}

float RayTriangleIntersection::getBrightness(std::vector<Light> lights, ObjModel &model) {
  float brightness = AMBIENT_LIGTHING_FACTOR; 

  // Loop through all the lights
  for (Light light : lights) {

    // Create a ray from the point to the light
    ModelPoint intersectionPoint = getIntersectionPoint();
    ModelPoint lightPoint = light.position();
    Ray lightRay = Ray(lightPoint, intersectionPoint);

    // Fire the ray with respect to the model and find out if there are any things between the model point and the light
    RayTriangleIntersection lightIntersectionPoint = model.getClosestIntersection(lightRay);

    if (!lightIntersectionPoint.isNull()) {
      if (glm::length(lightIntersectionPoint.getIntersectionPoint().getVec3() - intersectionPoint.getVec3()) < 0.01) {

        if (PROXIMITY_LIGTHING_FACTOR > 0) {
          float distanceFromLight = glm::length(lightPoint.getVec3() - intersectionPoint.getVec3()); 
          float lightIntensityAtPoint = light.intensity() / (4.0 * M_PI * distanceFromLight * distanceFromLight);
          brightness += lightIntensityAtPoint * PROXIMITY_LIGTHING_FACTOR;
        }
        
        if (INCIDENT_LIGTHING_FACTOR > 0) {
          glm::vec3 lightDirection = -lightRay.direction();
          float lightIntensityAtPoint = light.intensity() * glm::dot(normal(), lightDirection);

          if (lightIntensityAtPoint > 0.0) {
            brightness += lightIntensityAtPoint * INCIDENT_LIGTHING_FACTOR;
          }
        }
        
        if (SPECULAR_LIGTHING_FACTOR > 0) {
          Ray reflectedLightRay = lightRay.reflect(*this);
          float lightIntensityAtPoint = pow(glm::dot(_ray.direction(), reflectedLightRay.direction()), _intersectedTriangle.material().shinyness());

          if (lightIntensityAtPoint > 0.0) {
            brightness += lightIntensityAtPoint * SPECULAR_LIGTHING_FACTOR;
          }
        }
      }
    }
  }

  return brightness;
}
 
Colour RayTriangleIntersection::getColour(std::vector<Light> lights, ObjModel &model) {

  // Get the material at the intersected point
  int reflectionCount = 0;
  RayTriangleIntersection currentIntersection = *this;
  Ray currentRay = _ray;
  float currentReflectivity = 0.0f;
  
  Colour colour = Colour(0,0,0);
  
  // ---- Refraction and Reflection ---- //
  // If we hit something refractive create a refracted Ray and then recall refracted colour

  // While we are colliding with surfaces that are refractive or reflective
  while (
    !currentIntersection.isNull() &&
    (
      currentIntersection.getIntersectedTriangle().material().refractiveIndex() != -1 || 
      (
        reflectionCount < MAX_REFLECTIONS &&
        currentIntersection.getIntersectedTriangle().material().reflectivity() > 0.0
      )
    )
  ) 
  {
    ObjMaterial currentIntersectedMaterial = currentIntersection.getIntersectedTriangle().material();
    Colour currentColour = currentIntersection.getIntersectedTriangle().colour();
    float currentReflectivity = currentIntersectedMaterial.reflectivity();
    float currentRefractiveIndex = currentIntersectedMaterial.refractiveIndex();
        
    // If the material is transparent
    if (currentRefractiveIndex != -1) {
      currentRay = _ray.refract(*this);
    }
   
    // If the material is reflective
    else if (currentReflectivity != 0) {
    
      colour = colour + currentColour*(1-currentReflectivity);

      currentRay = _ray.reflect(*this);
      currentIntersection = model.getClosestIntersection(currentRay);
      reflectionCount++;
    }

    currentIntersection = model.getClosestIntersection(currentRay);
  }
   
  if (currentIntersection.isNull()) {
    colour = Colour(0,0,0);
  } else {
    colour = currentIntersection.getIntersectedTriangle().colour();
  }
  colour.setBrightness(getBrightness(lights, model));

  return colour;
}

CanvasPoint RayTriangleIntersection::getCanvasPoint(DrawingWindow &window, Camera camera, float scalar) {
	return _intersectionPoint.project(window, camera, scalar);
}

//void RayTriangleIntersection::draw(DrawingWindow &window, Camera camera, float scalar) {
//	CanvasPoint pointA = getCanvasPoint(window, camera, scalar);
//	pointA.draw(window, _intersectedObject.getMaterial().getColour());
//}

ModelTriangle RayTriangleIntersection::getIntersectedTriangle() {
	return _intersectedTriangle;
}

std::ostream &operator<<(std::ostream &os, RayTriangleIntersection &rti) {
	if (rti._isNull) {
		os << "Intersection is null";
	} else {
		os << "Intersection is at [" << rti._intersectionPoint.getVec3()[0] << "," << rti._intersectionPoint.getVec3()[1] << "," <<
		rti._intersectionPoint.getVec3()[2] << "] on triangle " << rti._intersectedTriangle <<
		" at a distance of " << rti._distanceFromOrigin;
	}
	return os;
}

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections) {
  RayTriangleIntersection closestIntersection;
  float currentShortestDistance = std::numeric_limits<float>::infinity();
  for (RayTriangleIntersection intersection: intersections) {
    if (intersection.getDistanceFromOrigin() < currentShortestDistance) {
      currentShortestDistance = intersection.getDistanceFromOrigin();
      closestIntersection = intersection;
    }
  }
  return closestIntersection;
}


