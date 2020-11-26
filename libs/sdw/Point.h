#pragma once

#include <iostream>
#include <glm/glm.hpp>

class Point {
	public:
        float x();
        float y();
        float z();

        friend std::ostream &operator<<(std::ostream &os, const Point &point);

	protected:
        glm::vec3 _point;
};
