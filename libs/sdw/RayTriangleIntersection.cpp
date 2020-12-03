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
	_distanceFromCamera = distance;
	_intersectedTriangle = triangle;
	_isNull = false;
}

bool RayTriangleIntersection::isNull() {
	return _isNull;
}

float RayTriangleIntersection::getDistanceFromCamera() {
	return _distanceFromCamera;
}

ModelPoint RayTriangleIntersection::getIntersectionPoint() {
	return _intersectionPoint;
}
 
Colour RayTriangleIntersection::getColour(std::vector<Light> lights, ObjModel model) {
  // TODO get colour if its a texture

  // Loop through all the lights
  for (Light light : lights) {

    // Create a ray from the point to the light
    ModelPoint intersectionPoint = getIntersectionPoint();
    ModelPoint lightPoint = light.position();
    Ray ray = Ray(lightPoint, intersectionPoint);

    // Fire the ray with respect to the model and find out if there are anyt hings between the model point and the light
    RayTriangleIntersection lightIntersectionPoint = model.getClosestIntersection(ray);

    if (!lightIntersectionPoint.isNull()) {
      if (glm::length(lightIntersectionPoint.getIntersectionPoint().getVec3() - intersectionPoint.getVec3()) < 0.01) {
        return getColour();
      } else {
        //std::cout << "Origin point: " << ray.origin().x << ", " << ray.origin().y << ray.origin().z << std::endl;
        //std::cout << "Direction: " << ray.direction().x << ", " << ray.direction().y << ray.direction().z << std::endl;
        //std::cout << "Ray intersected with something that is not the object" << std::endl;
        //std::cout << intersectionPoint << std::endl;
        //std::cout << lightIntersectionPoint << std::endl;
        //std::cout << lightPoint.x() << lightPoint.y() << lightPoint.z() << std::endl;
      }
    }
  }
  return Colour(0,0,0);
}

Colour RayTriangleIntersection::getColour() {
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
		" at a distance of " << rti._distanceFromCamera;
	}
	return os;
}

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections) {
  RayTriangleIntersection closestIntersection;
  float currentShortestDistance = std::numeric_limits<float>::infinity();
  for (RayTriangleIntersection intersection: intersections) {
    if (intersection.getDistanceFromCamera() < currentShortestDistance) {
      currentShortestDistance = intersection.getDistanceFromCamera();
      closestIntersection = intersection;
    }
  }
  return closestIntersection;
}


