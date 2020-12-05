#include "Ray.h"

Ray::Ray() = default;

// Create a ray that has the origin at the camera and is fired at a canvas point
Ray::Ray(CanvasPoint pixel, Camera &camera, DrawingWindow &window) {
  _origin= glm::vec3(camera.x(), camera.y(), camera.z());
  glm::vec3 pixelPosition = glm::vec3(
      camera.x() + pixel.x() - window.width / 2,
      camera.y() - (pixel.y() - window.height / 2),
      camera.z() - camera.getFocalLength()
  );
  setDirection(pixelPosition - _origin);
}

Ray::Ray(glm::vec3 origin, glm::vec3 point) {
  _origin = origin;
  setDirection(point - origin);
}

void Ray::setDirection(glm::vec3 direction) {
  _direction = direction;
  _direction = glm::normalize(_direction);
}

glm::vec3 Ray::direction() {
  return glm::normalize(_direction);
}

glm::vec3 Ray::origin() {
  return _origin;
}

Ray Ray::reflect(RayTriangleIntersection &intersection) {
  glm::vec3 normal = intersection.getIntersectedTriangle().normal();
  glm::vec3 reflectedDirection = direction() - 2.0f * normal * glm::dot(direction(), normal);

  return Ray(intersection.getIntersectionPoint().getVec3(), reflectedDirection);
}
