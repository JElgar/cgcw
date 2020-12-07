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

RayTriangleIntersection::RayTriangleIntersection(ModelPoint &point, float distance, ModelTriangle &triangle, Ray &ray, float e1Ratio, float e2Ratio) {
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
  if(_intersectedTriangle.v0().hasVertexNormal() && SHADING_MODE == Phong) {
    return _e0Ratio * _intersectedTriangle.v0().normal() +
           _e1Ratio * _intersectedTriangle.v1().normal() +
           _e2Ratio * _intersectedTriangle.v2().normal();
  }
  return _intersectedTriangle.normal();
}

float RayTriangleIntersection::getBrightness(std::vector<Light*> lights, ObjModel &model, std::vector<ModelTriangle> faces) {
  float brightness = AMBIENT_LIGTHING_FACTOR; 
 
  // -- Gouraud setup -- //
  std::vector<float> ratios;
  std::vector<glm::vec3> normals; 
  if (SHADING_MODE == Gouraud) {
    normals = {
      _intersectedTriangle.v0().normal(), 
      _intersectedTriangle.v1().normal(), 
      _intersectedTriangle.v2().normal()
    };
    
    ratios = {
      _e0Ratio,
      _e1Ratio,
      _e2Ratio,
    };
  }


  // Loop through all the lights
  for (Light* light : lights) {

    std::vector<ModelPoint> lightPoints = light->getLightPoints();
    float lightBrightness = 0;

    // Create a ray from the point to the light
    ModelPoint intersectionPoint = getIntersectionPoint();
    ModelPoint lightPoint = light->position();
    Ray lightRay = Ray(lightPoint, intersectionPoint);

    int numberOfLightPointsIntersected = 0;

    // Fire a ray at every point on the light and find out how many points we hit
    for (ModelPoint lightPointPoint : lightPoints) {
      Ray lightPointRay = Ray(lightPointPoint, intersectionPoint);
      RayTriangleIntersection lightIntersectionPoint = model.getClosestIntersection(lightPointRay);
      if (
        !lightIntersectionPoint.isNull() &&
        glm::length(lightIntersectionPoint.getIntersectionPoint().getVec3() - intersectionPoint.getVec3()) < 0.01 
      ) {
        numberOfLightPointsIntersected++;
      }
    }

    if (numberOfLightPointsIntersected != 0) {
      if (PROXIMITY_LIGTHING_FACTOR > 0) {
        float distanceFromLight = glm::length(lightPoint.getVec3() - intersectionPoint.getVec3()); 
        float lightIntensityAtPoint = light->intensity() / (4.0 * M_PI * distanceFromLight * distanceFromLight);
        lightBrightness += lightIntensityAtPoint * PROXIMITY_LIGTHING_FACTOR;
      }
      
      if (INCIDENT_LIGTHING_FACTOR > 0) {
        float lightIntensityAtPoint = 0;

        // If the shading mode is gourad calculate intersity with each normal and interpolate
        if (SHADING_MODE == Gouraud && _intersectedTriangle.v0().hasVertexNormal()) {
          for (int i = 0; i < normals.size(); i++) {
            lightIntensityAtPoint += ratios[i] * light->intensity() * glm::dot(normals[i], -lightRay.direction());
          }
        }

        else {
          lightIntensityAtPoint = light->intensity() * glm::dot(normal(), -lightRay.direction());
        }

        if (lightIntensityAtPoint > 0.0) {
          lightBrightness += lightIntensityAtPoint * INCIDENT_LIGTHING_FACTOR;
        }
      }
      
      if (SPECULAR_LIGTHING_FACTOR > 0) {
        float lightIntensityAtPoint = 0;

        // If the shading mode is gourad calculate intersity with each normal and interpolate
        if (SHADING_MODE == Gouraud && _intersectedTriangle.v0().hasVertexNormal()) {
          for (int i = 0; i < normals.size(); i++) {
            Ray reflectedLightRay = lightRay.reflect(*this, normals[i]);
            lightIntensityAtPoint += ratios[i] * pow(glm::dot(_ray.direction(), reflectedLightRay.direction()), _intersectedTriangle.material().shinyness());
          }
        } 
        
        else{
          Ray reflectedLightRay = lightRay.reflect(*this);
          lightIntensityAtPoint = pow(glm::dot(_ray.direction(), reflectedLightRay.direction()), _intersectedTriangle.material().shinyness());
        }

        if (lightIntensityAtPoint > 0.0) {
          lightBrightness += lightIntensityAtPoint * SPECULAR_LIGTHING_FACTOR;
        }
      }
    }
    brightness += lightBrightness * (numberOfLightPointsIntersected / lightPoints.size());
  }

  return brightness;
}

RayTriangleIntersection RayTriangleIntersection::bounce(ObjModel model, std::vector<ModelTriangle> faces) {
  int reflectionCount = 0;
  RayTriangleIntersection currentIntersection = *this;
  Ray currentRay = _ray;
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
    float currentReflectivity = currentIntersectedMaterial.reflectivity();
    float currentRefractiveIndex = currentIntersectedMaterial.refractiveIndex();
        
    // If the material is transparent
    if (currentRefractiveIndex != -1) {
      std::cout << "Refracting ray" << std::endl;
      currentRay = _ray.refract(currentIntersection);
    }
   
    // If the material is reflective
    else if (currentReflectivity != 0) {
      currentRay = _ray.reflect(currentIntersection);
      currentIntersection = model.getClosestIntersection(currentRay, faces);
      reflectionCount++;
    }

    currentIntersection = model.getClosestIntersection(currentRay, faces);
  }

  return currentIntersection;
}
 
Colour RayTriangleIntersection::getColour(std::vector<Light*> lights, ObjModel &model, std::vector<ModelTriangle> faces) {
  RayTriangleIntersection intersection = bounce(model, faces);
  Colour colour;
  if (intersection.isNull()) {
    colour = Colour(0,0,0);
  } else {
    colour = intersection.getIntersectedTriangle().colour();
  }
  colour.setBrightness(getBrightness(lights, model, faces));
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


