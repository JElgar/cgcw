#include "Ray.h"

Ray::Ray() = default;

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
  _origin = origin;
  _direction = direction/(float)(direction.length());
}

// Create a ray that has the origin at the camera and is fired at a canvas point
Ray::Ray(CanvasPoint pixel, Camera &camera, DrawingWindow &window) {
  _origin= glm::vec3(camera.x(), camera.y(), camera.z());
  glm::vec3 pixelPosition = glm::vec3(
      camera.x() + pixel.x() - window.width / 2,
      camera.y() - (pixel.y() - window.height / 2),
      camera.z() - camera.getFocalLength()
  );
  _direction = pixelPosition - _origin;
  _direction /= (float)_direction.length();
}

Ray::Ray(ModelPoint &origin, ModelPoint &point) {
  _origin = origin.getVec3();
  _direction = point.getVec3() - origin.getVec3();
  _direction /= (float)_direction.length();
}

void Ray::setDirection(glm::vec3 direction) {
  _direction = direction;
}

glm::vec3 Ray::direction() {
  return _direction;
}

glm::vec3 Ray::origin() {
  return _origin;
}

Ray Ray::reflect(RayTriangleIntersection &intersection) {
  glm::vec3 reflectedDirection = direction() - glm::vec3(2,2,2) * intersection.getIntersectedTriangle().normal() * (glm::dot(direction(), intersection.getIntersectedTriangle().normal()));
  
  return Ray(intersection.getIntersectionPoint().getVec3(), reflectedDirection);
}
