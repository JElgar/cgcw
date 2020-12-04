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
  _direction = pixelPosition - _origin;
}

Ray::Ray(glm::vec3 origin, glm::vec3 point) {
  _origin = origin;
  setDirection(point - origin);
}

void Ray::setDirection(glm::vec3 direction) {
  _direction = direction;
  glm::normalize(_direction);
}

glm::vec3 Ray::direction() {
  return _direction;
}

glm::vec3 Ray::origin() {
  return _origin;
}

Ray Ray::reflect(RayTriangleIntersection &intersection) {
  glm::vec3 norm = intersection.getIntersectedTriangle().normal();
  glm::vec3 reflectedDirection = direction() - glm::vec3(2,2,2) * norm * glm::dot(direction(), norm);
  
  std::cout << "Incident ray direction: " << direction().x << ", " << direction().y << ", " << direction().z << std::endl;
  std::cout << "Reflected ray direction: " << reflectedDirection.x << ", " << reflectedDirection.y << ", " << reflectedDirection.z << std::endl;
  
  return Ray(intersection.getIntersectionPoint().getVec3() + reflectedDirection, reflectedDirection);
}
