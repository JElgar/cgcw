#pragma once

#include <iostream>
#include <glm/glm.hpp>

class TexturePoint {
  private:
    glm::vec2 _point;

  public:
	TexturePoint();
	TexturePoint(float xPos, float yPos);
	TexturePoint(glm::vec2 point);
    const float x();
    const float y();
    const glm::vec2 point();
	friend std::ostream &operator<<(std::ostream &os, TexturePoint &point);
};

