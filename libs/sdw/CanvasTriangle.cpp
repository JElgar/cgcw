#include "CanvasTriangle.h"

CanvasTriangle::CanvasTriangle() = default;
CanvasTriangle::CanvasTriangle(const CanvasPoint &v0, const CanvasPoint &v1, const CanvasPoint &v2) {
    _vertices = {v0, v1, v2};
    orderVertices();
}

CanvasPoint &CanvasTriangle::v0() {
    return _vertices[0];
}

CanvasPoint &CanvasTriangle::v1() {
    return _vertices[1];
}

CanvasPoint &CanvasTriangle::v2() {
    return _vertices[2];
}

void CanvasTriangle::fillTriangle(Colour colour, DrawingWindow &window) {
  CanvasLine line01 = CanvasLine(v0(), v1());
  CanvasLine line12 = CanvasLine(v1(), v2());
  CanvasLine line02 = CanvasLine(v0(), v2());

  for (float y = v0().y(); y < v1().y(); y++) {
    CanvasPoint point1 = line01.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    CanvasLine line = CanvasLine(point1, point2);
    line.draw(colour, window);
  }

  for (float y = v1().y(); y < v2().y(); y++) {
    CanvasPoint point1 = line12.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    CanvasLine line = CanvasLine(point1, point2);
    line.draw(colour, window);
  }
}


void CanvasTriangle::mapTexture(TextureMap texture, DrawingWindow &window) {

  std::cout << "Mapping texture" << std::endl;

  orderVertices();
  CanvasLine line01 = CanvasLine(v0(), v1());
  CanvasLine line12 = CanvasLine(v1(), v2());
  CanvasLine line02 = CanvasLine(v0(), v2());

  std::cout << "y0: " << v0().y() << std::endl;
  std::cout << "y1: " << v1().y() << std::endl;
  std::cout << "y2: " << v2().y() << std::endl;

  
  float centrePointratio = (v1().y() - v0().y()) / (v2().y() - v0().y());
  TexturePoint intersectionTexturePoint = TexturePoint(
    v0().texturePoint().point() + (v2().texturePoint().point() - v0().texturePoint().point()) * centrePointratio
  );
  std::cout << "Centre point ratio is " << centrePointratio << std::endl;
  std::cout << "Centre point is " << intersectionTexturePoint << std::endl;

  
  // If the line is less than 1px thick skip drawing
  if (line01.length() < 1 || line12.length() < 1 || line02.length() < 1) {
    return;
  }

  int numberOfSteps = v1().y() - v0().y();

  std::vector<glm::vec2> line01TexturePoints = interpolate(v0().texturePoint().point(), v1().texturePoint().point(), numberOfSteps);
  std::vector<glm::vec2> line02TopTexturePoints = interpolate(v0().texturePoint().point(), intersectionTexturePoint.point(), numberOfSteps);
  
  std::cout << "Mapping top half" << std::endl;

  for (int y = v0().y(), i = 0; y < v1().y(); y++, i++) {
    std::cout << "y: " << y << std::endl;
    CanvasPoint point1 = line01.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);

    TexturePoint point1TextPoint = TexturePoint(line01TexturePoints[i]);
    TexturePoint point2TextPoint = TexturePoint(line02TopTexturePoints[i]);
    
    point1.setTexturePoint(point1TextPoint);
    point2.setTexturePoint(point2TextPoint);

    CanvasLine line = CanvasLine(point1, point2);
    line.mapTexture(texture, window);
  }

  std::vector<glm::vec2> line12TexturePoints = interpolate(v1().texturePoint().point(), v2().texturePoint().point(), v2().y() - v1().y());
  std::vector<glm::vec2> line02BottomTexturePoints = interpolate(intersectionTexturePoint.point(), v2().texturePoint().point(), v2().y() - v1().y());

  for (int y = v1().y(), i = 0; y < v2().y(); y++, i++) {
    CanvasPoint point1 = line12.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    
    TexturePoint point1TextPoint = TexturePoint(line12TexturePoints[i]);
    TexturePoint point2TextPoint = TexturePoint(line02BottomTexturePoints[i]);
    point1.setTexturePoint(point1TextPoint);
    point2.setTexturePoint(point2TextPoint);

    CanvasLine line = CanvasLine(point1, point2);
    line.mapTexture(texture, window);
  }
  
  std::cout << "Got to end of triangle" << std::endl;
}

void CanvasTriangle::draw(Colour colour, DrawingWindow &window) {
  CanvasLine(v0(), v1()).draw(colour, window);
  CanvasLine(v1(), v2()).draw(colour, window);
  CanvasLine(v2(), v0()).draw(colour, window);
  fillTriangle(colour, window);
}

//void CanvasTriangle::draw(TextureMap texture, Colour colour, DrawingWindow &window) {
//  mapTexture(texture, window);
//}

bool CanvasPointYComparitor(CanvasPoint & lhs, CanvasPoint & rhs) {
  return lhs.y() < rhs.y();
}

void CanvasTriangle::orderVertices() {
  std::sort(std::begin(_vertices), std::end(_vertices), CanvasPointYComparitor);
}

std::ostream &operator<<(std::ostream &os, CanvasTriangle &triangle) {
	os << triangle.v0() << triangle.v1() << triangle.v1();
	return os;
}
