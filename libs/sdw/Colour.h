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
		uint32_t pack();

		friend std::ostream &operator<<(std::ostream &os, const Colour &colour);
        bool operator==(Colour& rhs);
};
