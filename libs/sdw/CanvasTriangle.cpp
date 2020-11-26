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

//std::vector<uint32_t> CanvasTriangle::getColourValuesFromTexture(TextureMap texture, CanvasLine line) {
//  bool topHalf = line.v1().y < v1().y;
//
//  float ratioLeft;
//  // If we are in the top half of the triangle
//  if (topHalf) {
//    CanvasLine leftSub = CanvasLine(v0(), line.v0());
//    CanvasLine leftFull = CanvasLine(v0(), v1());
//    ratioLeft = leftSub.length() / leftFull.length();
//
//  } else {
//    CanvasLine leftSub = CanvasLine(v1(), line.v0());
//    CanvasLine leftFull = CanvasLine(v1(), v2());
//    ratioLeft = leftSub.length() / leftFull.length();
//  }
//
//  CanvasLine rightSub = CanvasLine(v0(), line.v1());
//  CanvasLine rightFull = CanvasLine(v0(), v2());
//  float ratioRight = rightSub.length() / rightFull.length();
//  if (ratioLeft > 1 || ratioRight > 1) {
//    return std::vector<uint32_t>();
//  }
//  CanvasPoint leftPointA;
//  CanvasPoint leftPointB;
//  if (topHalf) {
//    leftPointA = CanvasPoint(v0().getTexturePoint().x, v0().getTexturePoint().y);
//    leftPointB = CanvasPoint(v1().getTexturePoint().x, v1().getTexturePoint().y);
//  } else {
//    leftPointA = CanvasPoint(v1().getTexturePoint().x, v1().getTexturePoint().y);
//    leftPointB = CanvasPoint(v2().getTexturePoint().x, v2().getTexturePoint().y);
//  }
//  CanvasPoint rightPointA = CanvasPoint(v0().getTexturePoint().x, v0().getTexturePoint().y);
//  CanvasPoint rightPointB = CanvasPoint(v2().getTexturePoint().x, v2().getTexturePoint().y);
//
//  CanvasLine leftTextLine = CanvasLine(leftPointA, leftPointB);
//  CanvasLine rightTextLine = CanvasLine(rightPointA, rightPointB);
//
//  CanvasPoint leftTextPoint = leftTextLine.getPointFromRatio(ratioLeft);
//  CanvasPoint rightTextPoint = rightTextLine.getPointFromRatio(ratioRight);
//
//  std::vector<float> xVals = interpolateSingleFloats(leftTextPoint.x, rightTextPoint.x, (int)line.length());
//  std::vector<float> yVals = interpolateSingleFloats(leftTextPoint.y, rightTextPoint.y, (int)line.length());
//  std::vector<uint32_t> colourVals;
//  for (int i = 0; i < (int)line.length(); i++) {
//    colourVals.push_back(texture.getColourFromPoint(xVals[i], yVals[i]));
//  }
//  return colourVals;
//}

//void CanvasTriangle::mapTexture(TextureMap texture, DrawingWindow &window) {
//  orderVertices();
//  CanvasLine line01 = CanvasLine(v0(), v1());
//  CanvasLine line12 = CanvasLine(v1(), v2());
//  CanvasLine line02 = CanvasLine(v0(), v2());
//  if (line01.length() < 1 || line12.length() < 1 || line02.length() < 1) {
//    return;
//  }
//
//  for (int y = v0().y; y < v1().y; y++) {
//
//    CanvasPoint point1 = line01.findIntersectionWithY(y);
//    CanvasPoint point2 = line02.findIntersectionWithY(y);
//    CanvasLine line = CanvasLine(point1, point2);
//    std::vector<uint32_t> colourList = getColourValuesFromTexture(texture, line);
//    if (colourList.size() > 0) {
//      line.draw(colourList, window);
//    }
//  }
//
//
//  for (int y = v1().y; y < v2().y; y++) {
//    CanvasPoint point1 = line12.findIntersectionWithY(y);
//    CanvasPoint point2 = line02.findIntersectionWithY(y);
//
//    CanvasLine line = CanvasLine(point1, point2);
//    std::vector<uint32_t> colourList = getColourValuesFromTexture(texture, line);
//    if (colourList.size() > 0) {
//      line.draw(colourList, window);
//    }
//  }
//}

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
