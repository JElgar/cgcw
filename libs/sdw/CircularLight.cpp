#include "CircularLight.h"

CircularLight::CircularLight(glm::vec3 position, float intensity, float radius) {
  _position = position;
  _intensity = intensity;
  _radius = radius;
}

std::vector<ModelPoint> CircularLight::getLightPoints() {
  std::vector<ModelPoint> lightPoints;
  if (_radius == 0) {
    lightPoints.push_back(_position);
    return lightPoints;
  }
}
