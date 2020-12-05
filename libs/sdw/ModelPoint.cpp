#include "ModelPoint.h"

ModelPoint::ModelPoint() = default;
ModelPoint::ModelPoint(float x, float y, float z) {
  _point = glm::vec4(x, y, z, 1);
  _texturePoint = TexturePoint(-1,-1);
  _hasVertexNormal = false;
}

ModelPoint::ModelPoint(glm::vec3 point) {
  _point = glm::vec4(point.x, point.y, point.z, 1);
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

float ModelPoint::w() {
  return _point.w;
}

glm::vec3 ModelPoint::normal() {
  return _normal;
}

bool ModelPoint::hasVertexNormal() {
  return _hasVertexNormal;
}

glm::vec3 ModelPoint::getVec3() {
  return glm::vec3(x(), y(), z()); 
}

glm::vec4 ModelPoint::getVec4() {
  return _point; 
}

bool ModelPoint::hasTexturePoint() {
  return _texturePoint.x() >= 0 && _texturePoint.y() >= 0;
}

CanvasPoint ModelPoint::project(DrawingWindow &window, Camera &camera, float scalar) {

  glm::vec4 adjustedPoint = _point*camera.getWorldToCameraMatrix();
  
  float canvasX = camera.getFocalLength() * ((camera.x()-adjustedPoint.x)/(adjustedPoint.z-camera.z()));
  float canvasY = camera.getFocalLength() * ((adjustedPoint.y-camera.y())/(adjustedPoint.z-camera.z()));
  float canvasZ = adjustedPoint.z - camera.z();

  CanvasPoint point = CanvasPoint(
      canvasX*scalar + (float)(window.width/2),
      canvasY*scalar + (float)(window.height/2),
      canvasZ
  );

  if (hasTexturePoint()) {
    point.setTexturePoint(_texturePoint);
  }
  return point;

  //glm::vec4 projectedPoint = getVec4()*camera.getWorldToCameraMatrix();
  //projectedPoint /= projectedPoint.w;
  //projectedPoint = projectedPoint * camera._projectionMatrix;
  //projectedPoint /= projectedPoint.w;
  //
  //std::cout << "x" << projectedPoint.x << " " << projectedPoint.y << " " << projectedPoint.z << " " << projectedPoint.w << std::endl;

  //float x = (uint32_t)((1 - (projectedPoint[0] + 1) * 0.5) * window.width);
  //float y = (uint32_t)((1 - (projectedPoint[1] + 1) * 0.5) * window.height);

  //if (projectedPoint[0] < -1 || projectedPoint[0] > 1 || projectedPoint[1] < -1 || projectedPoint[1] > 1) return CanvasPoint();
////
  //CanvasPoint point = CanvasPoint(x, y, projectedPoint.z);
  // CanvasPoint point = CanvasPoint(projectedPoint[0] * 0.5 * window.width, projectedPoint[1] * 0.5 * window.height, projectedPoint[2]);
  // glm::mat4 projectionMatrix = glm::perspective(
  //   glm::radians(90.0), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
  //   1.0f,              // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
  //   0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
  //   100.0f             // Far clipping plane. Keep as little as possible.
  // );
  //

  //glm::vec4 projectedPoint = projectionMatrix*camera.getWorldToCameraMatrix()*modelPoint;

  //CanvasPoint point = CanvasPoint(projectedPoint.x, projectedPoint.y, projectedPoint.z);

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
