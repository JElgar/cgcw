#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Utils.h"
#include "TexturePoint.h"
#include "Colour.h"

class TextureMap {
public:
	size_t width;
	size_t height;
	std::vector<uint32_t> pixels;
	Colour getColourFromPoint(TexturePoint point);
	Colour getColourFromPoint(int x, int y);

	TextureMap();
	TextureMap(const std::string &filename);
	friend std::ostream &operator<<(std::ostream &os, const TextureMap &point);
};
