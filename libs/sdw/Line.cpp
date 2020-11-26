#include "Line.h"

float Line::length() {
  float xDiff = v0().x() - v1().x();
  float yDiff = v0().y() - v1().y();
  float len = std::sqrt(yDiff*yDiff + xDiff*xDiff);
  return len;
}


float Line::gradient() {
  if (((int)v1().x() == (int)v0().x())) {
    std::cout << "dividing by zero in gradient" << std::endl;
    throw std::runtime_error("dividing by zero in gradient");
  }
  return (v1().y() - v0().y()) / (v1().x() - v0().x());
}

Point Line::getPointFromRatio(float ratio) {
  float xCoord = v0().x() + (v1().x() - v0().x())*ratio;
  float yCoord = v0().y() + (v1().y() - v0().y())*ratio;
  return CanvasPoint(xCoord, yCoord);
}


Point Line::findIntersectionWithY(float y) {
  CanvasPoint point;

  if (int(v0().x()) == int(v1().x())) {
    point = CanvasPoint(v0().x(), y);
  } else if (gradient() == 0) {
    if (int(v0().y()) == y) {
      point = CanvasPoint(v0().x(), y);
    } else {
      std::cout << "Gradient of line is 0 in findIntersectionWithY" << std::endl;
      throw std::runtime_error("Gradient of line is 0 in findIntersectionWithY");
    }
  } else {
    float x = ((y - v0().y()) / gradient()) + v0().x();
    point = CanvasPoint(x, y);
  }
  float ratio = (point.x() - v0().x())/(v1().x() - v0().x());
  float z = v0().z() + (v1().z() - v0().z()) * ratio;
  CanvasPoint finalPoint = CanvasPoint(point.x(), point.y(), z);
  return finalPoint;
}

Point Line::v0() {
    return _points[0];
}

Point Line::v1() {
    return _points[1];
}

std::ostream &operator<<(std::ostream &os, Line &line) {
	os << line.v0() << line.v1();
	return os;
}

