#pragma once

#include <iostream>

class Colour {
	public:
		int red;
		int green;
		int blue;
		Colour();
		Colour(int r, int g, int b);
		Colour(uint32_t colour);
		friend std::ostream &operator<<(std::ostream &os, const Colour &colour);
		uint32_t pack();
};
