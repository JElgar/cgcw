#pragma once

#include "Light.h"

class CircularLight: public Light {
	public:
	  CircularLight();
	  CircularLight(glm::vec3 position, float intensity, float radius = 0);
      std::vector<ModelPoint> getLightPoints();

    private:
      float _radius;
};
