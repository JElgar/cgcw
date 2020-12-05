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


Ray::Ray(ModelPoint &origin, glm::vec3 direction) {
  _origin = origin.getVec3();
  setDirection(direction);
}

Ray::Ray(ModelPoint &origin, ModelPoint &point) {
  _origin = origin.getVec3();
  setDirection(point.getVec3() - origin.getVec3());
}

void Ray::setDirection(glm::vec3 direction) {
  _direction = direction;
  _direction = glm::normalize(_direction);
}

glm::vec3 Ray::direction() {
  return _direction;
}

glm::vec3 Ray::origin() {
  return _origin;
}

Ray Ray::reflect(RayTriangleIntersection &intersection) {
  glm::vec3 normal = intersection.normal();
  glm::vec3 reflectedDirection = direction() - normal * (float)(2.0*glm::dot(direction(), normal));

  ModelPoint origin = intersection.getIntersectionPoint();
  ModelPoint adjustedOrigin = ModelPoint(origin.getVec3() + SHADOW_BIAS*normal);
  return Ray(adjustedOrigin, reflectedDirection);
}
