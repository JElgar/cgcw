#pragma once

#include <glm/glm.hpp>

class Light{
	public:
	  Light();
	  explicit Light(glm::vec3 position);

      glm::vec3 position();

    private:
      glm::vec3 _position;
};
