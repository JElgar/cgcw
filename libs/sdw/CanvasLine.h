#pragma once
#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <math.h>

#include "DrawingWindow.h"
#include "Colour.h"
#include "CanvasPoint.h"
#include "Utils.h"

class CanvasLine {
	private:
        std::vector<CanvasPoint> _vertices;
	public:
		CanvasLine();
		CanvasLine(const CanvasPoint &v0, const CanvasPoint &v1);
		//CanvasLine(const TexturePoint &v0, const TexturePoint &v1);
        
        CanvasPoint v0();
		CanvasPoint v1();

		float length();
		float gradient();

		CanvasPoint findIntersectionWithY(float y);
		CanvasPoint getPointFromRatio(float ratio);

		friend std::ostream &operator<<(std::ostream &os, const CanvasLine &line);
        
		void draw(Colour colour, DrawingWindow &window);
		void draw(std::vector<Colour> colourList, DrawingWindow &window);
};
