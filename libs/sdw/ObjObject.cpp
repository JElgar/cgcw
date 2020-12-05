#include "ObjObject.h"

ObjObject::ObjObject() {
  _hasMaterial = false;
};
ObjObject::ObjObject(std::string name) {
  _name = name;
  _hasMaterial = false; 
}

std::string ObjObject::getName() {
  return _name;
}

void ObjObject::setMaterial(ObjMaterial material) {
  _material = material;
  _hasMaterial = true; 
}

std::vector<ModelTriangle> ObjObject::getFaces() {
  return _faces;
}

ObjMaterial ObjObject::getMaterial() {
  return _material;
}

bool ObjObject::hasMaterial() {
  return _hasMaterial;
}

void ObjObject::draw(DrawingWindow &window, Camera &camera, float scalar) {
    if (!hasMaterial()) {
      for (ModelTriangle &triangle: _faces) {
        Colour defaultColour = Colour(255, 0, 0);
        triangle.draw(defaultColour, window, camera, scalar);
      }
    } else if (_material.hasTexture()){
      for (ModelTriangle &triangle: _faces) {
        triangle.draw(_material.getTexture(), window, camera, scalar);
      }
    } else {
      for (ModelTriangle &triangle: _faces) {
        triangle.draw(_material.getColour(), window, camera, scalar);
    }
  }
}

void ObjObject::addFace(ModelPoint v0, ModelPoint v1, ModelPoint v2, ObjMaterial &material) {
  ModelTriangle newTriangle = ModelTriangle(v0, v1, v2);
  newTriangle.setMaterial(material);
  _faces.push_back(newTriangle);
}


RayTriangleIntersection ObjObject::getClosestIntersection(Ray &ray) {
  std::vector<RayTriangleIntersection> intersections;
  for (ModelTriangle triangle: getFaces()) {
    RayTriangleIntersection possibleIntersection = triangle.getClosestIntersection(ray);
    if (!possibleIntersection.isNull()) {
      intersections.push_back(possibleIntersection);
    }
  }
  return ::getClosestIntersection(intersections);
}
