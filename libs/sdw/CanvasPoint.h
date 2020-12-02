#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "DrawingWindow.h"
#include "TextureMap.h"

class CanvasPoint {
	public:
		CanvasPoint();
		CanvasPoint(float xPos, float yPos);
		CanvasPoint(glm::vec3 point);
		CanvasPoint(float xPos, float yPos, float zPos);
		CanvasPoint(glm::vec3 point, Colour &colour);
		CanvasPoint(float xPos, float yPos, float zPos, Colour &colour);
		CanvasPoint(glm::vec3 point, TexturePoint &texturePoint);
		CanvasPoint(glm::vec3 point, glm::vec2 texturePoint);
		CanvasPoint(float xPos, float yPos, float zPos, TexturePoint &texturePoint);

        const float x();
        const float y();
        const float z();
        const glm::vec3 point();
        TexturePoint texturePoint();
        const Colour getColour();

        void setColour(Colour &colour);
        void setZ(float z);

        const bool isOffScreen(DrawingWindow &window);

        void draw(DrawingWindow &window);
        void draw(TextureMap &texture, DrawingWindow &window);
		
        void setTexturePoint(TexturePoint &texturePoint);
		
        friend std::ostream &operator<<(std::ostream &os, const CanvasPoint &point);

	private:
        glm::vec3 _point;
        Colour _colour;
        TexturePoint _texturePoint;
};

bool CanvasPointYComparitor(CanvasPoint & lhs, CanvasPoint & rhs);
