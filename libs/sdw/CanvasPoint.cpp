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

CanvasPoint::CanvasPoint(float x, float y, float z, Colour &colour) {
  _point = glm::vec3(x, y, z);
  _colour = colour;
}


float CanvasPoint::x() {
  return _point.x;
}

float CanvasPoint::y() {
  return _point.y;
}

float CanvasPoint::z() {
  return _point.z;
}

Colour CanvasPoint::getColour() {
  return _colour;
}


bool CanvasPoint::isOffScreen(DrawingWindow &window) {
  return !window.pixelOnScreen(x(), y());
}


void CanvasPoint::draw(DrawingWindow &window) {
  window.setPixel(x(), y(), z(), _colour);
}


std::ostream &operator<<(std::ostream &os, const CanvasPoint &point) {
	os << "(" << point._point.x << ", " << point._point.y << ", " << point._point.z << ") " <<  "  " << point._colour;
	return os;
}

//TexturePoint CanvasPoint::getTexturePoint() {
//	return _texturePoint;
//}

//void CanvasPoint::addTexturePoint(TexturePoint texturePoint) {
//	_texturePoint = texturePoint;
//}
//
