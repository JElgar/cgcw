#include "Point.h"

float Point::x() {
  return _point.x;
}

float Point::y() {
  return _point.y;
}

float Point::z() {
  return _point.z;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
	os << "(" << point._point.x << ", " << point._point.y << ", " << point._point.z << ") ";
	return os;
}

