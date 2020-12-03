#pragma once

#include <glm/glm.hpp>
#include "ModelPoint.h"

class Light{
	public:
	  Light();
	  explicit Light(glm::vec3 position);

      ModelPoint position();

    private:
      glm::vec3 _position;
};
