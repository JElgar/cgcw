#include "ObjMaterial.h"

ObjMaterial::ObjMaterial() = default;
ObjMaterial::ObjMaterial(std::string name) {
  _name = name;
  _hasTexture = false;
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
