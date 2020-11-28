#include "TexturePoint.h"

TexturePoint::TexturePoint() = default;
TexturePoint::TexturePoint(float x, float y) {
  _point = glm::vec2(x, y);
}
TexturePoint::TexturePoint(glm::vec2 point) {
  _point = point;
}

const float TexturePoint::x() {
  return _point.x;
}

const float TexturePoint::y() {
  return _point.y;
}

const glm::vec2 TexturePoint::point() {
  return _point;
}

std::ostream &operator<<(std::ostream &os, TexturePoint &point) {
	os << "x: " << point.x() << " y: " << point.y();
	return os;
}
