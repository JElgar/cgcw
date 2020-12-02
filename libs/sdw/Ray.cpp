#include "Ray.h"

Ray::Ray(glm::vec3 pVector, glm::vec3 dVector) {
  _positionVector = pVector;
  _directionVector = dVector/(float)(dVector.length());
}

Ray::Ray(CanvasPoint pixel, Camera &camera, DrawingWindow &window) {
  _positionVector = glm::vec3(camera.x(), camera.y(), camera.z());
  glm::vec3 pixelPosition = glm::vec3(
      camera.x() + pixel.x() - window.width / 2,
      camera.y() + pixel.y() - window.height / 2,
      camera.z()-camera.getFocalLength()
  );
  _directionVector = pixelPosition - _positionVector;
  _directionVector /= (float)_directionVector.length();
}

glm::vec3 Ray::directionVector() {
  return _directionVector;
}

glm::vec3 Ray::positionVector() {
  return _positionVector;
}
