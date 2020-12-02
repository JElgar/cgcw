#pragma once
#include <math.h>
#include <glm/glm.hpp>

class Camera {
  private:
    //glm::vec4 _positionVector;
    glm::mat4 _cameraToWorldMatrix;
    glm::mat4 _worldToCameraMatrix;
    float _focalLength;

  public:
    //glm::mat4 _projectionMatrix;
    float x();
    float y();
    float z();
    glm::vec3 getVec3();

    Camera(float x, float y, float z, float focalLength);
    glm::mat4 getCameraToWorldMatrix();
    glm::mat4 getWorldToCameraMatrix();
    void setCameraToWorldMatrix(glm::mat4 matrix);
    float getFocalLength();
    void translate(float x, float y, float z);
    void rotate(float yaw, float pitch, float roll);
    void rotateInPlace(float yaw, float pitch, float roll);
};
