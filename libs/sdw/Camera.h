#pragma once
#include <math.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Utils.h"
#include "CameraWayPoint.h"
#include "CameraTransition.h"

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
    void lookAt(glm::vec3 point);
    void setPosition(glm::vec3 position);
    void orbitX(float angle);


    void wayPointTransition(CameraWayPoint &from, CameraWayPoint &to, int frame, int startingFrame = 0);
    void transition(std::vector<CameraWayPoint> &wayPoints, int frame, int startingFrame = 0);
    void transition(CameraTransition &transition, int frame);
};
