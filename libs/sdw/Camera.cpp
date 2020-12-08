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

void Camera::setPosition(glm::vec3 position) {
  _position = position;
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
    
void Camera::lookAt(glm::vec3 point) {
  glm::vec3 forward = glm::normalize(glm::vec3(_position - point));
  glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
  glm::vec3 up = glm::cross(forward, right);
  _orientation[0] = right;
  _orientation[1] = up;
  _orientation[2] = forward;
}

void Camera::wayPointTransition(CameraWayPoint &from, CameraWayPoint &to, int frame, int startingFrame) {

  int frames = to.frames();
  
  if (frame > frames + startingFrame || frame < startingFrame) {
    return;
  }

  // If this transiation takes no time just do it
  if (frames == 0) {
    if (startingFrame == frame) {
      std::cout << "Updating the camera position" << std::endl;
      _position = to.position();
      lookAt(to.lookAt());
    }
    return;
  }

  // Otherwise interpolate between values
  std::vector<glm::vec3> positions = interpolate(from.position(), to.position(), frames);
  std::vector<glm::vec3> lookAtPoints = interpolate(from.lookAt(), to.lookAt(), frames);

  _position = positions[frame - startingFrame];
  lookAt(lookAtPoints[frame - startingFrame]);
}
    
void Camera::transition(CameraTransition &transition, int frame) {
  int relativeFrame = frame - transition.startFrame();
  if (relativeFrame >= transition.frames() || relativeFrame < 0) {
    return;
  }

  // Find current transition
  int indexFrame = 0;
  for (int i = 0; i < transition.wayPoints().size(); i++) {
  
    CameraWayPoint currentWayPoint = transition.wayPoints()[i];

    if (indexFrame <= frame && indexFrame + transition.wayPoints()[i].frames() >= frame) {
      // If we are still looking at the first waypoint
      if (i == 0) {
        setPosition(currentWayPoint.position());
        lookAt(currentWayPoint.lookAt());
        return;
      }

      CameraWayPoint previousWayPoint = transition.wayPoints()[i-1];
      wayPointTransition(previousWayPoint, currentWayPoint, relativeFrame - indexFrame);
    }
  
    indexFrame += currentWayPoint.frames();
  }

}
