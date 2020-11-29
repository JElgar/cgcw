#pragma once
#include <iostream>
#include <stdio.h>
#include "Colour.h"
#include "TextureMap.h"

class ObjMaterial {
  public:
    ObjMaterial();
  	ObjMaterial(std::string name);

    std::string getName();
    Colour &getColour();
    TextureMap &getTexture();

    void setColour(Colour colour);
    void setTexture(TextureMap texture);
    
    bool hasTexture();

  	friend std::ostream &operator<<(std::ostream &os, const ObjMaterial &material);

  private:
    std::string _name;
  	Colour _colour;
    TextureMap _texture;
    bool _hasTexture;
};
