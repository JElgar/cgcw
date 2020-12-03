#pragma once

#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "ModelTriangle.h"
#include "Colour.h"
#include "Light.h"

class ObjModel;

class RayTriangleIntersection {
	public:
		RayTriangleIntersection();
		RayTriangleIntersection(ModelPoint &point, float distance, ModelTriangle &triangle);
		// RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle, const ObjObject &object);
		
		float getDistanceFromCamera();
		ModelTriangle getIntersectedTriangle();
		ModelPoint getIntersectionPoint();
        Colour getColour(std::vector<Light> lights, ObjModel model);
        Colour getColour();
		CanvasPoint getCanvasPoint(DrawingWindow &window, Camera camera, float scalar);
        bool isNull();

		void draw(DrawingWindow &window, Camera camera, float scalar, Colour colour);
		friend std::ostream& operator<<(std::ostream &os, RayTriangleIntersection &rti);
	
    private:
		ModelPoint _intersectionPoint;
		float _distanceFromCamera;
		ModelTriangle _intersectedTriangle;
		bool _isNull;
};

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections);

#include "ObjModel.h"
