#pragma once

#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "ModelTriangle.h"
#include "Colour.h"
#include "Light.h"
#include "Ray.h"

class ObjModel;

class RayTriangleIntersection {
	public:
		RayTriangleIntersection();
		RayTriangleIntersection(ModelPoint &point, float distance, ModelTriangle &triangle, Ray &ray);
		// RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle, const ObjObject &object);
		
		float getDistanceFromOrigin();
		ModelTriangle getIntersectedTriangle();
		ModelPoint getIntersectionPoint();
        Colour getColour(std::vector<Light> lights, ObjModel &model);
        Colour getColour(ObjModel &model);
        Ray ray();
		CanvasPoint getCanvasPoint(DrawingWindow &window, Camera camera, float scalar);
        bool isNull();

		void draw(DrawingWindow &window, Camera camera, float scalar, Colour colour);
		friend std::ostream& operator<<(std::ostream &os, RayTriangleIntersection &rti);
	
    private:
		ModelPoint _intersectionPoint;
		float _distanceFromOrigin;
		ModelTriangle _intersectedTriangle;
		bool _isNull;
        Ray _ray;
};

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections);

#include "ObjModel.h"
