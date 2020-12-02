#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include "Utils.h"
#include <iostream>
#include "ModelPoint.h"
#include "ModelTriangle.h"
#include "ObjObject.h"
#include "ObjMaterial.h"
#include "Colour.h"
//#include "Ray.h"
#include <algorithm>

class ObjModel {
  public:
    ObjModel(std::string fileLocation, std::string filename, float vScalar);
    std::vector<ObjObject> getObjects();
    
    RayTriangleIntersection getClosestIntersection(Ray &ray, Camera &camera);
    void draw(DrawingWindow &window, Camera &camera, float scalar);
    void drawRayTracing(DrawingWindow &window, Camera &camera, float scalar);

  private:
    std::vector<ObjObject> _objects;
};
    
std::vector<ObjMaterial> loadMaterials(std::string fileLocation, std::string filename);
