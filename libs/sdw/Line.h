#include "Shape.h"

class Line : Shape {
	public:
		Point v0();
		Point v1();

		float length();
		float gradient();

		Point findIntersectionWithY(float y);
		Point getPointFromRatio(float ratio);

		friend std::ostream &operator<<(std::ostream &os, const Line &line);
};
