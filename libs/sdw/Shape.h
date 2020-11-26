#pragma once

#include <vector>
#include "Point.h"

class Shape {
	protected:
        std::vector<Point> _vertices;

    public:
	  Point operator[](size_t i) const;
	  Point &operator[](size_t i);
};
