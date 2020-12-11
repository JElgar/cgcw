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
    float reflectivity();
    float shinyness();
    float refractiveIndex();

    void setColour(Colour colour);
    void setTexture(TextureMap texture);
    void setReflectivity(float reflectivity);
    void setRefractiveIndex(float reflectivity);
    void setIsNull(bool isNull);
    void setName(std::string name);
    
    bool hasTexture();
    bool isNull();

  	friend std::ostream &operator<<(std::ostream &os, const ObjMaterial &material);

  private:
    std::string _name;
  	Colour _colour;
    TextureMap _texture;
    bool _hasTexture;
    bool _isNull;
    float _reflectivity;
    float _shinyness;
    float _refractiveIndex;
};
