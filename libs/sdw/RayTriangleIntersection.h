#pragma once

#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "ModelTriangle.h"
#include "Colour.h"

class RayTriangleIntersection {
	public:
		RayTriangleIntersection();
		RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle);
		// RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle, const ObjObject &object);
		
		float getDistanceFromCamera();
		ModelTriangle getIntersectedTriangle();
		glm::vec3 getIntersectionPoint();
        Colour getColour();
		CanvasPoint getCanvasPoint(DrawingWindow &window, Camera camera, float scalar);
        bool isNull();

		void draw(DrawingWindow &window, Camera camera, float scalar, Colour colour);
		friend std::ostream& operator<<(std::ostream &os, const RayTriangleIntersection &rti);
	
    private:
		glm::vec3 _intersectionPoint;
		float _distanceFromCamera;
		ModelTriangle _intersectedTriangle;
		bool _isNull;
};

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections);
