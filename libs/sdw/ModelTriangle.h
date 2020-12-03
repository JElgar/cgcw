#pragma once

#include <string>
#include <vector>
#include <utility>
#include <glm/glm.hpp>

#include "Colour.h"
#include "TexturePoint.h"
#include "ModelPoint.h"
#include "CanvasTriangle.h"
#include "TextureMap.h"
#include "Ray.h"
#include "ObjMaterial.h"

class RayTriangleIntersection;

class ModelTriangle {
	public:
		ModelTriangle();
		ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2);

		ModelPoint v0();
		ModelPoint v1();
		ModelPoint v2();
        ObjMaterial material();

        void setMaterial(ObjMaterial &material);

		CanvasTriangle project(DrawingWindow &window, Camera &camera, float scalar);
		void draw(Colour &colour, DrawingWindow &window, Camera &camera, float scalar);
		void draw(TextureMap &texture, DrawingWindow &window, Camera &camera, float scalar);

        RayTriangleIntersection getClosestIntersection(Ray &ray, Camera &camera);

		friend std::ostream &operator<<(std::ostream &os, ModelTriangle triangle);

	private:
        std::vector<ModelPoint> _vertices;
        ObjMaterial _material;
};

#include "RayTriangleIntersection.h"
