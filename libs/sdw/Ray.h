#pragma once

#include <glm/glm.hpp>
#include "Utils.h"
#include "Camera.h"
#include "CanvasPoint.h"
#include "ModelPoint.h"

class RayTriangleIntersection;

class Ray {
  public:
    Ray();
    Ray(glm::vec3 origin, glm::vec3 point);
    Ray(CanvasPoint pixel, Camera &camera, DrawingWindow &window);
    
    glm::vec3 origin();
    glm::vec3 direction();

    void setDirection(glm::vec3 direction);

    Ray reflect(RayTriangleIntersection &intersection);

  private:
    glm::vec3 _origin;
    glm::vec3 _direction;
};

#include "RayTriangleIntersection.h"
