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
    glm::vec3 getVec3();
    glm::vec4 getVec4();
    glm::vec3 normal();

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    TexturePoint texturePoint();
    void setTexturePoint(TexturePoint texturePoint);
    void setNormal(glm::vec3 normal);
    bool hasTexturePoint();
    bool hasVertexNormal();
    
    CanvasPoint project(DrawingWindow &window, Camera &camera, float scalar);
    void translate(glm::vec3 translation, float scale = 1.0);
    
    ModelPoint operator-(ModelPoint &rhs);
    bool operator==(ModelPoint &rhs);
    bool operator!=(ModelPoint &rhs);
		
    friend std::ostream &operator<<(std::ostream &os, ModelPoint &point);

  private:
    glm::vec3 _point;
    TexturePoint _texturePoint;
    glm::vec3 _normal;
    bool _hasVertexNormal;
};
