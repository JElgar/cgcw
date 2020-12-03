#include "ObjMaterial.h"

ObjMaterial::ObjMaterial() {
  _hasTexture = false;
  _reflectivity = 0.0;
}

ObjMaterial::ObjMaterial(std::string name) {
  _name = name;
  _hasTexture = false;
  _reflectivity = 0.0;
}

void ObjMaterial::setColour(Colour colour) {
  _colour = colour;
}

void ObjMaterial::setTexture(TextureMap texture) {
  _hasTexture = true;
  _texture = texture;
}

Colour &ObjMaterial::getColour() {
  return _colour;
}

float ObjMaterial::reflectivity() {
  return _reflectivity;
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

std::ostream &operator<<(std::ostream &os, const ObjMaterial &material) {
  os << material._name << ": " << material._colour << std::endl;
  return os;
}
