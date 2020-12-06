#include "ObjMaterial.h"

ObjMaterial::ObjMaterial() {
  _isNull = true;
  _hasTexture = false;
  _reflectivity = 0.0;
  _shinyness = 128.0;
  _refractiveIndex = -1.0;
}

ObjMaterial::ObjMaterial(std::string name) {
  _name = name;
  _hasTexture = false;
  _reflectivity = 0.0;
  _shinyness = 128.0;
  _isNull = false;
  _refractiveIndex = -1.0;
}

void ObjMaterial::setColour(Colour colour) {
  _colour = colour;
  _isNull = false;
}

void ObjMaterial::setTexture(TextureMap texture) {
  _hasTexture = true;
  _texture = texture;
  _isNull = false;
}

void ObjMaterial::setReflectivity(float reflectivity) {
  _reflectivity = reflectivity;
}

void ObjMaterial::setRefractiveIndex(float refractiveIndex) {
  _refractiveIndex = refractiveIndex;
}

Colour &ObjMaterial::getColour() {
  return _colour;
}

float ObjMaterial::shinyness() {
  return _shinyness;
}

float ObjMaterial::reflectivity() {
  return _reflectivity;
}

float ObjMaterial::refractiveIndex() {
  return _refractiveIndex;
}

std::string ObjMaterial::getName() {
  return _name;
}

TextureMap &ObjMaterial::getTexture() {
  return _texture;
}

bool ObjMaterial::hasTexture() {
  return _hasTexture;
}

bool ObjMaterial::isNull() {
  return _isNull;
}

std::ostream &operator<<(std::ostream &os, const ObjMaterial &material) {
  os << material._name << ": " << material._colour << std::endl;
  return os;
}
