#pragma once

#include <iostream>
#include <algorithm>
#include <utility>

class Colour {
	public:
		Colour();
		Colour(int r, int g, int b);
		Colour(uint32_t colour);

		int red;
		int green;
		int blue;
        float brightness;

        void setRed(int red);
        void setGreen(int green);
        void setBlue(int green);

		uint32_t pack();
        void setBrightness(float brightness); 

		friend std::ostream &operator<<(std::ostream &os, const Colour &colour);
        bool operator==(Colour &rhs);
        void operator*=(float intensity);
        Colour operator*(float intensity);
        Colour operator+(Colour colour);
};
