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

    const float x();
    const float y();
    const float z();
    const float w();
    const glm::vec4 getVec4();

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
