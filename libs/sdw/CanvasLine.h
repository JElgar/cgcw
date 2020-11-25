#pragma once
#include "CanvasPoint.h"
#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include "Colour.h"
#include <math.h>
#include "DrawingWindow.h"
#include "Line.h"

class CanvasLine: public Line {
	public:
		CanvasLine();
		CanvasLine(const CanvasPoint &v0, const CanvasPoint &v1);
		//CanvasLine(const TexturePoint &v0, const TexturePoint &v1);
        
		bool isOffScreen(DrawingWindow &window);

		void draw(Colour colour, DrawingWindow &window);
		void draw(std::vector<Colour> colourList, DrawingWindow &window);
};
