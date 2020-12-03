#pragma once

#include <glm/glm.hpp>
#include "ModelPoint.h"

class Light{
	public:
	  Light();
	  explicit Light(glm::vec3 position);
	  Light(glm::vec3 position, float intensity);

      ModelPoint position();
      float intensity();

    private:
      glm::vec3 _position;
      float _intensity;
};
