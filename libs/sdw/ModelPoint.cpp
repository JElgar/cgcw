#include "ModelPoint.h"

ModelPoint::ModelPoint() = default;
ModelPoint::ModelPoint(float x, float y, float z) {
  _point = glm::vec3(x, y, z);
  _texturePoint = TexturePoint(-1,-1);
  _hasVertexNormal = false;
}

ModelPoint::ModelPoint(glm::vec3 point) {
  _point = point;
  _texturePoint = TexturePoint(-1,-1);
  _hasVertexNormal = false;
}

void ModelPoint::setTexturePoint(TexturePoint texturePoint) {
  _texturePoint = texturePoint;
}

void ModelPoint::setNormal(glm::vec3 normal) {
  _normal = normal;
  _hasVertexNormal = true;
}

TexturePoint ModelPoint::texturePoint() {
  return _texturePoint;
}

float ModelPoint::x() {
  return _point.x;
}

float ModelPoint::y() {
  return _point.y;
}

float ModelPoint::z() {
  return _point.z;
}

glm::vec3 ModelPoint::normal() {
  return _normal;
}

bool ModelPoint::hasVertexNormal() {
  return _hasVertexNormal;
}

glm::vec3 ModelPoint::getVec3() {
  return _point; 
}

glm::vec4 ModelPoint::getVec4() {
  return glm::vec4(x(), y(), z(), 1); 
}

bool ModelPoint::hasTexturePoint() {
  return _texturePoint.x() >= 0 && _texturePoint.y() >= 0;
}

CanvasPoint ModelPoint::project(DrawingWindow &window, Camera &camera, float scalar) {

  glm::vec3 adjustedPointPosition = _point - camera.getVec3();
  glm::vec3 adjustedPoint = adjustedPointPosition * camera.getOrientationMatrix();
  
  float canvasX = camera.getFocalLength() * (-adjustedPoint.x/adjustedPoint.z);
  float canvasY = camera.getFocalLength() * (adjustedPoint.y/adjustedPoint.z);
  float canvasZ = adjustedPoint.z;

  CanvasPoint point = CanvasPoint(
      canvasX*scalar + (float)(window.width/2),
      canvasY*scalar + (float)(window.height/2),
      canvasZ
  );

  if (hasTexturePoint()) {
    point.setTexturePoint(_texturePoint);
  }
  return point;
}

std::ostream &operator<<(std::ostream &os, ModelPoint &point) {
  os << "(" << point.x() << ", "<< point.y() << ", " << point.z() << ")";
  return os;
}

bool ModelPoint::operator==(ModelPoint &rhs) {
  bool equal = x() == rhs.x() && y() == rhs.y() && z() == rhs.z();
  return equal;
}

bool ModelPoint::operator!=(ModelPoint &rhs) {
  return !(x() == rhs.x() && y() == rhs.y() && z() == rhs.z());
}
