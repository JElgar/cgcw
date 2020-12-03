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

RayTriangleIntersection::RayTriangleIntersection(ModelPoint &point, float distance, ModelTriangle &triangle) {
	_intersectionPoint = point;
	_distanceFromOrigin = distance;
	_intersectedTriangle = triangle;
	_isNull = false;
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
 
Colour RayTriangleIntersection::getColour(std::vector<Light> lights, ObjModel model) {
  // TODO get colour if its a texture
  float brightness = 0.2; 

  // Loop through all the lights
  for (Light light : lights) {

    // Create a ray from the point to the light
    ModelPoint intersectionPoint = getIntersectionPoint();
    ModelPoint lightPoint = light.position();
    Ray ray = Ray(lightPoint, intersectionPoint);

    // Fire the ray with respect to the model and find out if there are anyt hings between the model point and the light
    RayTriangleIntersection lightIntersectionPoint = model.getClosestIntersection(ray);

    if (!lightIntersectionPoint.isNull()) {
      if (glm::length(lightIntersectionPoint.getIntersectionPoint().getVec3() - intersectionPoint.getVec3()) < 0.0001) {
        float distanceFromLight = glm::length(lightPoint.getVec3() - intersectionPoint.getVec3()); 
        float lightIntensityAtPoint = light.intensity() / (4 * M_PI * distanceFromLight * distanceFromLight);

        brightness += lightIntensityAtPoint;
      } 
    }
  }
  Colour pixelColour = getColour();
  pixelColour *= brightness;
  return pixelColour;
}

Colour RayTriangleIntersection::getColour() {
  ObjMaterial intersectedMaterial = _intersectedTriangle.material();
  if (intersectedMaterial.reflectivity() == 0.0) {
    return _intersectedTriangle.colour();
  }
     
  return _intersectedTriangle.colour();
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


