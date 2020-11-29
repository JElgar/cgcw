#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Colour.h"
#include "TexturePoint.h"
#include "ModelPoint.h"
#include "CanvasTriangle.h"
#include "TextureMap.h"

class ModelTriangle {
	public:
		ModelTriangle();
		ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2);

		ModelPoint v0();
		ModelPoint v1();
		ModelPoint v2();

		CanvasTriangle project(DrawingWindow &window, Camera &camera, float scalar);
		void draw(Colour &colour, DrawingWindow &window, Camera &camera, float scalar);
		void draw(TextureMap &texture, DrawingWindow &window, Camera &camera, float scalar);
		friend std::ostream &operator<<(std::ostream &os, ModelTriangle triangle);

	private:
        std::vector<ModelPoint> _vertices;
};
