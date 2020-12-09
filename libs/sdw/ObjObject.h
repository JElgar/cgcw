#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

#include "Utils.h"
#include "ModelPoint.h"
#include "ModelTriangle.h"
#include "ObjMaterial.h"

class RayTriangleIntersection;

class ObjObject {
  public:
    ObjObject(std::string name);
    ObjObject();
    std::string getName();
    ObjMaterial getMaterial();
    bool hasMaterial();

    void addFace(ModelPoint v0, ModelPoint v1, ModelPoint v2, ObjMaterial &material);
    void draw(DrawingWindow &window, Camera &camera, float scalar);
    void fill(DrawingWindow &window, Camera &camera, float scalar);
    std::vector<ModelTriangle> getFaces();
    void setMaterial(ObjMaterial material);
    void translate(glm::vec3 translation, float scale = 1.0);

    RayTriangleIntersection getClosestIntersection(Ray &ray);

  private:
    std::string _name;
    ObjMaterial _material;
    std::vector<ModelTriangle> _faces;
    bool _hasMaterial = false;
};

#include "RayTriangleIntersection.h"
