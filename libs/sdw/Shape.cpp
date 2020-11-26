#include "Shape.h"

Point Shape::operator[](size_t i) const {
    return _vertices[i];
}

Point &Shape::operator[](size_t i) {
    return _vertices[i];
}


