#pragma once
#include <glm/glm.hpp>

class CameraWayPoint {
  public:
    CameraWayPoint();
    CameraWayPoint(glm::vec3 position, glm::vec3 lookAt, int frames = 0);
    glm::vec3 position();
    glm::vec3 lookAt();
    int frames();

  private:
    glm::vec3 _position;
    glm::vec3 _lookAt;
    // Frame for the transiation to the new position and orientation to take
    int _frames;

};
