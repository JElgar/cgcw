#include "CanvasPoint.h"

CanvasPoint::CanvasPoint() {
  // _texturePoint = TexturePoint(-1, -1);
}

CanvasPoint::CanvasPoint(float x, float y) {
  _point = glm::vec3(x, y, -1);
}

CanvasPoint::CanvasPoint(float x, float y, float z) {
  _point = glm::vec3(x, y, z);
}

CanvasPoint::CanvasPoint(glm::vec3 point, Colour &colour) {
  _point = point;
  _colour = colour;
}

CanvasPoint::CanvasPoint(float x, float y, float z, Colour &colour) {
  _point = glm::vec3(x, y, z);
  _colour = colour;
}

CanvasPoint::CanvasPoint(glm::vec3 point, TexturePoint &texturePoint) {
  _point = point;
  _texturePoint = texturePoint;
}

CanvasPoint::CanvasPoint(glm::vec3 point, glm::vec2 texturePoint) {
  _point = point;
  _texturePoint = TexturePoint(texturePoint);
}

CanvasPoint::CanvasPoint(float x, float y, float z, TexturePoint &texturePoint) {
  _point = glm::vec3(x, y, z);
  _texturePoint = texturePoint;
}


const float CanvasPoint::x() {
  return _point.x;
}

const float CanvasPoint::y() {
  return _point.y;
}

const float CanvasPoint::z() {
  return _point.z;
}

const glm::vec3 CanvasPoint::point() {
  return _point;
}

const Colour CanvasPoint::getColour() {
  return _colour;
}

TexturePoint CanvasPoint::texturePoint() {
	return _texturePoint;
}

const bool CanvasPoint::isOffScreen(DrawingWindow &window) {
  return !window.pixelOnScreen(x(), y());
}


void CanvasPoint::draw(DrawingWindow &window) {
  window.setPixel(x(), y(), z(), _colour);
}

void CanvasPoint::draw(TextureMap &texture, DrawingWindow &window) {
  Colour colour = texture.getColourFromPoint(texturePoint());
  window.setPixel(x(), y(), z(), colour);
}


void CanvasPoint::setTexturePoint(TexturePoint &texturePoint) {
	_texturePoint = texturePoint;
}


std::ostream &operator<<(std::ostream &os, const CanvasPoint &point) {
	os << "(" << point._point.x << ", " << point._point.y << ", " << point._point.z << ") " <<  "  " << point._colour;
	return os;
}

bool CanvasPointYComparitor(CanvasPoint & lhs, CanvasPoint & rhs) {
  return lhs.y() < rhs.y();
}


