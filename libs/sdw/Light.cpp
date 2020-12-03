#include "Light.h"

Light::Light(glm::vec3 position) {
  _position = position;
  _intensity = 1.0;
}

Light::Light(glm::vec3 position, float intensity) {
  _position = position;
  _intensity = intensity;
}

ModelPoint Light::position() {
  return ModelPoint(_position);
}

float Light::intensity() {
  return _intensity;
}
