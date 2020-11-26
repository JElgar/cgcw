#pragma once

#include <iostream>
#include <array>
#include <algorithm>

#include "DrawingWindow.h"
#include "CanvasPoint.h"
#include "CanvasLine.h"
#include "Triangle.h"
//#include "TextureMap.h"

class CanvasTriangle : public Triangle {
	public:
		CanvasTriangle();
		CanvasTriangle(const CanvasPoint &v0, const CanvasPoint &v1, const CanvasPoint &v2);
		
        void fillTriangle(Colour colour, DrawingWindow &window);
		void draw(Colour colour, DrawingWindow &window);
		
        //void mapTexture(TextureMap texture, DrawingWindow &window);
		//void draw(TextureMap texture, Colour colour, DrawingWindow &window);
        //std::vector<uint32_t> getColourValuesFromTexture(TextureMap texture, CanvasLine line);
		
        // bool isOffScreen(DrawingWindow &window);
        
        friend std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle);
};
