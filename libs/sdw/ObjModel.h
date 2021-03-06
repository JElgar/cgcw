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
    ObjModel(std::vector<ObjObject> objects);
    std::vector<ObjObject> getObjects();
    std::vector<ModelTriangle> getFaces();
    
    RayTriangleIntersection getClosestIntersection(Ray &ray);
    RayTriangleIntersection getClosestIntersection(Ray &ray, std::vector<ModelTriangle> faces);
    void drawWireframe(DrawingWindow &window, Camera &camera, float scalar);
    void drawRasterize(DrawingWindow &window, Camera &camera, float scalar);
    void drawRayTracing(DrawingWindow &window, Camera &camera, std::vector<Light*> lights, float scalar);
    void draw(DrawingWindow &window, Camera &camera, std::vector<Light*> lights, float scalar);
        
    void translate(glm::vec3 translation, float scale = 1.0);
    ObjModel operator+(ObjModel model);

  private:
    std::vector<ObjObject> _objects;
};
    
#include "RayTriangleIntersection.h"
#include "ObjObject.h"

std::vector<ObjMaterial> loadMaterials(std::string fileLocation, std::string filename);


