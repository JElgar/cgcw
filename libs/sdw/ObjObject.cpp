#include "ObjObject.h"

ObjObject::ObjObject() = default;
ObjObject::ObjObject(std::string name) {
  _name = name;
}

std::string ObjObject::getName() {
  return _name;
}

void ObjObject::setMaterial(ObjMaterial material) {
  _material = material;
}

std::vector<ModelTriangle> ObjObject::getFaces() {
  return _faces;
}

ObjMaterial ObjObject::getMaterial() {
  return _material;
}

void ObjObject::draw(DrawingWindow &window, Camera &camera, float scalar) {
    if (_material.hasTexture()){
      for (ModelTriangle &triangle: _faces) {
        triangle.draw(_material.getTexture(), window, camera, scalar);
      }
    } else {
      for (ModelTriangle &triangle: _faces) {
        triangle.draw(_material.getColour(), window, camera, scalar);
    }
  }
}

void ObjObject::addFace(ModelPoint v0, ModelPoint v1, ModelPoint v2) {
  ModelTriangle newTriangle = ModelTriangle(v0, v1, v2);
  _faces.push_back(newTriangle);
}
