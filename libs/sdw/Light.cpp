#include "Light.h"

ModelPoint Light::position() {
  return ModelPoint(_position);
}

float Light::intensity() {
  return _intensity;
}
