#pragma once
#include <math.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Utils.h"

class Camera {
  private:
    glm::mat3 _orientation;
    glm::vec3 _position;
    float _focalLength;

  public:
    //glm::mat4 _projectionMatrix;
    float x();
    float y();
    float z();
    glm::vec3 getVec3();
    glm::mat3 getOrientationMatrix();

    Camera(float x, float y, float z, float focalLength);
    float getFocalLength();
    void translate(float x, float y, float z);
    void rotate(float yaw, float pitch, float roll);
    void rotateInPlace(float yaw, float pitch, float roll);
};
