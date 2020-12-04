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
#include "ObjMaterial.h"

class RayTriangleIntersection;
class Ray;

class ModelTriangle {
	public:
		ModelTriangle();
		ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2);

		ModelPoint v0();
		ModelPoint v1();
		ModelPoint v2();
        ObjMaterial material();
        Colour colour();

        void setMaterial(ObjMaterial &material);

		CanvasTriangle project(DrawingWindow &window, Camera &camera, float scalar);
		void draw(Colour &colour, DrawingWindow &window, Camera &camera, float scalar);
		void draw(TextureMap &texture, DrawingWindow &window, Camera &camera, float scalar);
        glm::vec3 normal();

        RayTriangleIntersection getClosestIntersection(Ray &ray);

		friend std::ostream &operator<<(std::ostream &os, ModelTriangle triangle);

	private:
        std::vector<ModelPoint> _vertices;
        ObjMaterial _material;
        glm::vec3 _normal;
};

#include "RayTriangleIntersection.h"
#include "Ray.h"
