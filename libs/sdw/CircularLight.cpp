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

  for (float x = -_radius; x < _radius; x+=LIGHT_RESOLUTION) {
    for (float y = -_radius; y < _radius; y+=LIGHT_RESOLUTION) {
      for (float z = -_radius; z < _radius; z+=LIGHT_RESOLUTION) {
        if (x*x + y*y + z*z < std::pow(_radius, 3)) {
          lightPoints.push_back(ModelPoint(_position.x + x, _position.y + y, _position.z + z));
        }
      }
    }
  }
  return lightPoints;
}
