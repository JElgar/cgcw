#include "Colour.h"

Colour::Colour() = default;
Colour::Colour(int r, int g, int b) {
  red = r;
  green = g;
  blue = b;
}
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

void Colour::setBrightness(float brightness) {
  this->brightness = brightness;
}

bool Colour::operator==(Colour& rhs) {
  return pack() == rhs.pack();
}

uint32_t Colour::pack() {
  return (255 << 24) + (red << 16) + (green << 8) + blue;
}

void Colour::setRed(int value) {
  red = std::min(value, 255);
}

void Colour::setGreen(int value) {
  green = std::min(value, 255);
}

void Colour::setBlue(int value) {
  blue = std::min(value, 255);
}
    
void Colour::operator*=(float intensity) {
  setRed(red * intensity);
  setGreen(green * intensity);
  setBlue(blue * intensity);
}
        
Colour Colour::operator*(float value) {
  Colour c = *this;
  c *= value;
  return c;
}

Colour Colour::operator+(Colour colour) {
  Colour c;
  c.setRed(red + colour.red);
  c.setGreen(green + colour.green);
  c.setBlue(blue + colour.blue);
  return c;
}
