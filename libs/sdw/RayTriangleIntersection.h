#pragma once

#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "ModelTriangle.h"
#include "Colour.h"
#include "Light.h"
#include "Ray.h"
#include "Global.h"

class ObjModel;

class RayTriangleIntersection {
	public:
		RayTriangleIntersection();
		RayTriangleIntersection(ModelPoint &point, float distance, ModelTriangle &triangle, Ray &ray, float e0Ration, float e1Ratio);
		// RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle, const ObjObject &object);
		
		float getDistanceFromOrigin();
		ModelTriangle getIntersectedTriangle();
		ModelPoint getIntersectionPoint();
        Ray ray();
		CanvasPoint getCanvasPoint(DrawingWindow &window, Camera camera, float scalar);
        bool isNull();
        glm::vec3 normal();

        // Get colour with brightness values applied
        Colour getColour(std::vector<Light> lights, ObjModel &model, std::vector<ModelTriangle> faces);
        float getBrightness(std::vector<Light> lights, ObjModel &model, std::vector<ModelTriangle> faces);

		void draw(DrawingWindow &window, Camera camera, float scalar, Colour colour);
        RayTriangleIntersection bounce(ObjModel model, std::vector<ModelTriangle> faces);
		friend std::ostream& operator<<(std::ostream &os, RayTriangleIntersection &rti);
	
    private:
		ModelPoint _intersectionPoint;
		float _distanceFromOrigin;
		ModelTriangle _intersectedTriangle;
		bool _isNull;
        Ray _ray;

        float _e0Ratio;
        float _e1Ratio;
        float _e2Ratio;
};

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections);

#include "ObjModel.h"
