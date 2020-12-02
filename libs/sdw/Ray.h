#pragma once

#include <glm/glm.hpp>
#include "Utils.h"
#include "Camera.h"
#include "CanvasPoint.h"


class Ray {
  public:
    Ray(glm::vec3 pVector, glm::vec3 dVector);
    Ray(CanvasPoint pixel, Camera &camera, DrawingWindow &window);
    
    glm::vec3 positionVector();
    glm::vec3 directionVector();

  private:
    glm::vec3 _positionVector;
    glm::vec3 _directionVector;
};
