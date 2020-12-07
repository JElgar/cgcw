#pragma once

#include <glm/glm.hpp>
#include "ModelPoint.h"
#include "Global.h"

class Light{
	public:
      ModelPoint position();
      float intensity();

      virtual std::vector<ModelPoint> getLightPoints() {
        std::cout << "CircularLight in the LIGHTS OH NO!" << std::endl;
        std::vector<ModelPoint> points;
        points.push_back(_position);
        return points;
      }

    protected:
      glm::vec3 _position;
      float _intensity;
};
