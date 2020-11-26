#pragma once
#include <iostream>
#include <math.h>
#include <algorithm>
#include <math.h>

#include "DrawingWindow.h"
#include "CanvasPoint.h"
#include "Line.h"

class CanvasLine: public Line {
	public:
		CanvasLine();
		CanvasLine(CanvasPoint &v0, CanvasPoint &v1);
		CanvasLine(CanvasPoint v0, CanvasPoint v1);
		//CanvasLine(const TexturePoint &v0, const TexturePoint &v1);
        
		bool isOffScreen(DrawingWindow &window);

		void draw(Colour colour, DrawingWindow &window);
		void draw(std::vector<Colour> colourList, DrawingWindow &window);
};
