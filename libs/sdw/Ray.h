#pragma once

#include <glm/glm.hpp>
#include "Utils.h"
#include "Camera.h"
#include "CanvasPoint.h"
#include "ModelPoint.h"


class Ray {
  public:
    Ray(glm::vec3 origin, glm::vec3 direction);
    Ray(CanvasPoint pixel, Camera &camera, DrawingWindow &window);
    Ray(ModelPoint &origin, ModelPoint &point);
    
    glm::vec3 origin();
    glm::vec3 direction();

    void setDirection(glm::vec3 direction);

  private:
    glm::vec3 _origin;
    glm::vec3 _direction;
};
