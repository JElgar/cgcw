#include "Colour.h"
#include <utility>

Colour::Colour() = default;
Colour::Colour(int r, int g, int b) : red(r), green(g), blue(b) {}
Colour::Colour(uint32_t colour) {
    red = (colour >> 16) & 0xff;
    green = (colour >> 8) & 0xff;
    blue = colour  & 0xff;
}

std::ostream &operator<<(std::ostream &os, const Colour &colour) {
	os << colour.red << ", "
	   << colour.green << ", "
	   << colour.blue << "]";
	return os;
}

bool Colour::operator==(Colour& rhs) {
  return pack() == rhs.pack();
}

uint32_t Colour::pack() {
  return (255 << 24) + (red << 16) + (green << 8) + blue;
}
