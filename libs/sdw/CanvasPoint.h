#pragma once

//#include "TexturePoint.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Point.h"
#include "Colour.h"
#include "DrawingWindow.h"

class CanvasPoint : public Point {
	public:
		CanvasPoint();
		CanvasPoint(float xPos, float yPos);
		CanvasPoint(float xPos, float yPos, float zPos);
		CanvasPoint(glm::vec3 point);
		
        CanvasPoint &v0();
		CanvasPoint &v1();
		CanvasPoint &v2();

        Colour getColour();

        bool isOffScreen(DrawingWindow &window);
		
        //void addTexturePoint(TexturePoint texturePoint);
		//TexturePoint getTexturePoint();
		
        friend std::ostream &operator<<(std::ostream &os, const CanvasPoint &point);

	private:
        Colour _colour;
		
        //TexturePoint _texturePoint;
};
