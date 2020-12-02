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

RayTriangleIntersection::RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle) {
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

glm::vec3 RayTriangleIntersection::getIntersectionPoint() {
	return _intersectionPoint;
}

CanvasPoint RayTriangleIntersection::getCanvasPoint(DrawingWindow &window, Camera camera, float scalar) {
	ModelPoint point = ModelPoint(_intersectionPoint[0], _intersectionPoint[1], _intersectionPoint[2]);
	return point.project(window, camera, scalar);
}

//void RayTriangleIntersection::draw(DrawingWindow &window, Camera camera, float scalar) {
//	CanvasPoint pointA = getCanvasPoint(window, camera, scalar);
//	pointA.draw(window, _intersectedObject.getMaterial().getColour());
//}

ModelTriangle RayTriangleIntersection::getIntersectedTriangle() {
	return _intersectedTriangle;
}

std::ostream &operator<<(std::ostream &os, const RayTriangleIntersection &rti) {
	if (rti._isNull) {
		os << "Intersection is null";
	} else {
		os << "Intersection is at [" << rti._intersectionPoint[0] << "," << rti._intersectionPoint[1] << "," <<
		rti._intersectionPoint[2] << "] on triangle " << rti._intersectedTriangle <<
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


