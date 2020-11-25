#include "CanvasPoint.h"

class Line {
	protected:
		CanvasPoint _v0;
		CanvasPoint _v1;
	public:
		CanvasPoint v0();
		CanvasPoint v1();

		float length();
		float gradient();

		CanvasPoint findIntersectionWithY(float y);
		CanvasPoint getPointFromRatio(float ratio);

		friend std::ostream &operator<<(std::ostream &os, const Line &line);
};
