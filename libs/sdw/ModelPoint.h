#pragma once
#include <iostream>
#include "DrawingWindow.h"
#include "CanvasPoint.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

class ModelPoint {
  public:
    ModelPoint();
    ModelPoint(float x, float y, float z);
    ModelPoint(glm::vec3);

    float x();
    float y();
    float z();
    float w();
    glm::vec3 getVec3();
    glm::vec4 getVec4();

    TexturePoint texturePoint();
    void setTexturePoint(TexturePoint texturePoint);
    bool hasTexturePoint();
    
    CanvasPoint project(DrawingWindow &window, Camera &camera, float scalar);
    
    ModelPoint operator-(ModelPoint rhs);
		
    friend std::ostream &operator<<(std::ostream &os, const ModelPoint point);

  private:
    glm::vec4 _point;
    TexturePoint _texturePoint;
};
