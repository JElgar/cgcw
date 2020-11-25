#pragma once

//#include "TexturePoint.h"
#include <iostream>
#include "DrawingWindow.h"
#include <glm/glm.hpp>

class CanvasPoint {
	public:
		CanvasPoint();
		CanvasPoint(float xPos, float yPos);
		CanvasPoint(float xPos, float yPos, float zPos);
		CanvasPoint(glm::vec3 point);

        float x();
        float y();
        float z();
        Colour getColour();

        bool isOffScreen(DrawingWindow &window);
		
        //void addTexturePoint(TexturePoint texturePoint);
		//TexturePoint getTexturePoint();
		
        friend std::ostream &operator<<(std::ostream &os, const CanvasPoint &point);

	private:
        glm::vec3 _point;
        Colour _colour;
		
        //TexturePoint _texturePoint;
};
