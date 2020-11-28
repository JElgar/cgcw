#include "CanvasLine.h"

CanvasLine::CanvasLine() = default;
CanvasLine::CanvasLine(const CanvasPoint &v0, const CanvasPoint &v1) {
  _vertices = {v0, v1};
  orderVertices();
}


float CanvasLine::length() {
  float xDiff = v0().x() - v1().x();
  float yDiff = v0().y() - v1().y();
  float len = std::sqrt(yDiff*yDiff + xDiff*xDiff);
  return len;
}


float CanvasLine::gradient() {
  if (((int)v1().x() == (int)v0().x())) {
    std::cout << "dividing by zero in gradient" << std::endl;
    throw std::runtime_error("dividing by zero in gradient");
  }
  return (v1().y() - v0().y()) / (v1().x() - v0().x());
}

CanvasPoint CanvasLine::getPointFromRatio(float ratio) {
  float xCoord = v0().x() + (v1().x() - v0().x())*ratio;
  float yCoord = v0().y() + (v1().y() - v0().y())*ratio;
  return CanvasPoint(xCoord, yCoord);
}


CanvasPoint CanvasLine::findIntersectionWithY(float y) {

  if (!inRange(y, v0().y(), v1().y())) {
    std::cout << "y " << y << "out of range in findIntersectionWithY" << std::endl;
    return CanvasPoint();
  }
  
  if (v0().y() - v1().y() == 0) {
    std::cout << "Gradient of line is 0 in findIntersectionWithY" << std::endl;
    return CanvasPoint();
  }

  float ratio = (y - v0().y())/(v1().y() - v0().y());
  float x = v0().x() + (v1().x() - v0().x()) * ratio;
  float z = v0().z() + (v1().z() - v0().z()) * ratio;
  return CanvasPoint(x, y, z);
}

CanvasPoint CanvasLine::v0() {
    return _vertices[0];
}

CanvasPoint CanvasLine::v1() {
    return _vertices[1];
}


void CanvasLine::draw(Colour colour, DrawingWindow &window) {
  std::vector<Colour> colourList = {colour};
  draw(colourList, window);
}

void CanvasLine::mapTexture(TextureMap &texture, DrawingWindow &window) {
  
  float distanceX = v1().x() - v0().x();
  float distanceY = v1().y() - v0().y();
  int numberOfSteps = std::ceil(std::max(std::abs(distanceX), std::abs(distanceY)))+1;

  std::vector<glm::vec2> textPoints = interpolate(v0().texturePoint().point(), v1().texturePoint().point(), numberOfSteps);
  std::vector<glm::vec3> points = interpolate(v0().point(), v1().point(), numberOfSteps);
  
  for (int i = 0; i < numberOfSteps; i++) {
    TexturePoint texturePoint = TexturePoint(textPoints[i]);
    CanvasPoint point = CanvasPoint(points[i], texturePoint);
    point.draw(texture, window);
  }
}
		

void CanvasLine::draw(std::vector<Colour> colourList, DrawingWindow &window) {

  float distanceX = v1().x() - v0().x();
  float distanceY = v1().y() - v0().y();

  // If the line is less than 1 pixel long dont draw it
  if (length() >= 1) {

    // Get the points between v0 and v1 which to draw
    int numberOfSteps = std::ceil(std::max(std::abs(distanceX), std::abs(distanceY)))+1;
    std::vector<glm::vec3> points = interpolate(v0().point(), v1().point(), numberOfSteps);
    
    for (int i = 0; i < numberOfSteps; i++) {
      Colour colour;
      if (colourList.size() == 1) {
        colour = colourList[0];
      } else {
        colour = colourList[i];
      }

      CanvasPoint(points[i], colour).draw(window);
    }

  }
}


void CanvasLine::orderVertices() {
  std::sort(std::begin(_vertices), std::end(_vertices), CanvasPointYComparitor);
}

std::ostream &operator<<(std::ostream &os, CanvasLine &line) {
	os << line.v0() << line.v1();
	return os;
}
