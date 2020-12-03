#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Utils.h"
#include "ModelPoint.h"
#include "ObjMaterial.h"
#include "Colour.h"
#include "Ray.h"
#include "Light.h"

class RayTriangleIntersection;
class ObjObject;

class ObjModel {
  public:
    ObjModel(std::string fileLocation, std::string filename, float vScalar);
    std::vector<ObjObject> getObjects();
    
    RayTriangleIntersection getClosestIntersection(Ray &ray);
    void draw(DrawingWindow &window, Camera &camera, float scalar);
    void drawRayTracing(DrawingWindow &window, Camera &camera, std::vector<Light> lights, float scalar);

  private:
    std::vector<ObjObject> _objects;
};
    
#include "RayTriangleIntersection.h"
#include "ObjObject.h"

std::vector<ObjMaterial> loadMaterials(std::string fileLocation, std::string filename);


