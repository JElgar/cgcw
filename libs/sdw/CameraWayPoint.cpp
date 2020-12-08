#include "CameraWayPoint.h"

CameraWayPoint::CameraWayPoint(glm::vec3 position, glm::vec3 lookAt, int frames) {
  _position = position; 
  _lookAt = lookAt; 
  _frames = frames;
}

glm::vec3 CameraWayPoint::position() {
  return _position; 
}

glm::vec3 CameraWayPoint::lookAt() {
  return _lookAt; 
}

int CameraWayPoint::frames() {
  return _frames; 
}
