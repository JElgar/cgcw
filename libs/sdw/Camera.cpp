#include "Camera.h"

Camera::Camera(float x, float y, float z, float focalLength) {
  _focalLength = focalLength;
  _position = glm::vec3(x, y, z);
  _orientation = glm::mat3(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
  );
}

float Camera::x() {
  return _position.x;
}

float Camera::y() {
  return _position.y;
}

float Camera::z() {
  return _position.z;
}

glm::mat3 Camera::getOrientationMatrix() {
  return _orientation;
}

glm::vec3 Camera::getVec3() {
  return _position;
}

float Camera::getFocalLength() {
  return _focalLength;
}

void Camera::rotate(float yaw, float pitch, float roll) {
  glm::mat3 rotMatrix = rotationMatrix(yaw, pitch, roll);
  _orientation = _orientation * rotMatrix;
  
  rotMatrix = rotationMatrix(-yaw, -pitch, -roll);
  _position = _position * rotMatrix;
}

void Camera::translate(float x, float y, float z) {
  glm::vec3 transVector = glm::vec3(x, y, z);
  _position += transVector;
}

void Camera::rotateInPlace(float yaw, float pitch, float roll) {
  glm::mat3 rotMatrix = rotationMatrix(yaw, pitch, roll);
  _orientation = _orientation * rotMatrix;
}
