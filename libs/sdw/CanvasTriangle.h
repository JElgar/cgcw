#pragma once

#include "CanvasPoint.h"
#include "CanvasLine.h"
#include <iostream>
#include <algorithm>
#include "Colour.h"
#include "DrawingWindow.h"
//#include "TextureMap.h"

class CanvasTriangle {
	public:
		CanvasTriangle();
		CanvasTriangle(const CanvasPoint &v0, const CanvasPoint &v1, const CanvasPoint &v2);

		CanvasPoint &v0();
		CanvasPoint &v1();
		CanvasPoint &v2();
		
        void fillTriangle(Colour &colour, DrawingWindow &window);
		void draw(Colour &colour, DrawingWindow &window);
		void mapTexture(TextureMap &texture, DrawingWindow &window);
		
        void orderVertices();
		
		friend std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle);

    private:
        std::vector<CanvasPoint> _vertices;
};

void mapTextureBetween2Lines(CanvasLine &lineLeft, CanvasLine &lineRight, TextureMap &texture, DrawingWindow &window);
