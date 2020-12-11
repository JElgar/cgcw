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

CanvasPoint CanvasTriangle::getFurthestPointFromCamera() {
  // Copy verticies so we dont reorder actual values
  std::vector<CanvasPoint> verticies = _vertices;
  std::sort(std::begin(verticies), std::end(verticies), CanvasPointZComparitor);
  return verticies[0];
}

CanvasPoint CanvasTriangle::getClosestPointFromCamera() {
  // Copy verticies so we dont reorder actual values
  std::vector<CanvasPoint> verticies = _vertices;
  std::sort(std::begin(verticies), std::end(verticies), CanvasPointZComparitor);
  return verticies[2];
}

void CanvasTriangle::fill(Colour &colour, DrawingWindow &window) {
  CanvasLine line01 = CanvasLine(v0(), v1());
  CanvasLine line12 = CanvasLine(v1(), v2());
  CanvasLine line02 = CanvasLine(v0(), v2());

  // Fill top half of traingle
  for (float y = v0().y(); y < v1().y(); y++) {
    CanvasPoint point1 = line01.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    CanvasLine line = CanvasLine(point1, point2);
    line.draw(colour, window);
  }

  // Fill bottom half of traingle
  for (float y = v1().y(); y < v2().y(); y++) {
    CanvasPoint point1 = line12.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    CanvasLine line = CanvasLine(point1, point2);
    line.draw(colour, window);
  }
}


void mapTextureBetween2Lines(CanvasLine &lineLeft, CanvasLine &lineRight, TextureMap &texture, DrawingWindow &window, int rasterizingRow, CanvasTriangle &triangle) {

  if (lineLeft.v0().y() != lineRight.v0().y() || lineLeft.v1().y() != lineRight.v1().y()) {
    std::cerr << "Cannot texture between 2 line with different start or end y values";
    return;
  }

  // Find the number of lines that need to be textured
  int numberOfSteps = lineLeft.v1().y() - lineLeft.v0().y();

  // Get all the texture points along the two lines (one per y value)
  std::vector<glm::vec2> lineLeftTexturePoints = interpolate(lineLeft.v0().texturePoint().point(), lineLeft.v1().texturePoint().point(), numberOfSteps);
  std::vector<glm::vec2> lineRightTexturePoints = interpolate(lineRight.v0().texturePoint().point(), lineRight.v1().texturePoint().point(), numberOfSteps);

  CanvasPoint closestPoint = triangle.getClosestPointFromCamera();
  CanvasPoint furtherstPoint = triangle.getFurthestPointFromCamera();
  //std::cout << "INITAL VALS" << std::endl;
  float z0 = furtherstPoint.z();
  //std::cout << z0 << std::endl;
  float z1 = closestPoint.z();
  //std::cout << z1 << std::endl;
  float c0 = furtherstPoint.texturePoint().y();
  //std::cout << c0 << std::endl;
  float c1 = closestPoint.texturePoint().y();
  //std::cout << c1 << std::endl;

  // Go through each line that is to be textured
  for (float y = lineLeft.v0().y(), i = 0; y < lineLeft.v1().y() && i < numberOfSteps; y++, i++) {

    // Get the line by finding the points on each line that intersect the current y value
    CanvasPoint point1 = lineLeft.findIntersectionWithY(y);
    CanvasPoint point2 = lineRight.findIntersectionWithY(y);
   
    TexturePoint point1TextPoint;
    TexturePoint point2TextPoint;
    if (PERSPECTIVE_CORRECTION_TEXTURING) {
      float q = rasterizingRow + i;
      float c = ((c0 / z0)*(1.0f - q) + (c1/z1)*q) / ((1.0f / z0)*(1.0f - q) + (1/z1)*q);
      std::cout << c << std::endl;

      point1TextPoint = TexturePoint(lineLeftTexturePoints[i].x, c);
      point2TextPoint = TexturePoint(lineRightTexturePoints[i].x, c);
    } 
    else {
      // Get the texture point out of the list 
      point1TextPoint = TexturePoint(lineLeftTexturePoints[i]);
      point2TextPoint = TexturePoint(lineRightTexturePoints[i]);
    }
    
    // Set the texture points 
    point1.setTexturePoint(point1TextPoint);
    point2.setTexturePoint(point2TextPoint);

    // Create and texture the line
    CanvasLine line = CanvasLine(point1, point2);
    line.mapTexture(texture, window);
  }
} 


void CanvasTriangle::mapTexture(TextureMap &texture, DrawingWindow &window) {

  // Find the central point's texture point so we can interpolate the sides between
  // By central we mean with the same y value as v1 
  float centrePointRatio = (v1().y() - v0().y()) / (v2().y() - v0().y());
  CanvasPoint centerPoint = CanvasPoint(
    // Set the point
    v0().point() + (v2().point() - v0().point()) * centrePointRatio,
    // Set the texture
    v0().texturePoint().point() + (v2().texturePoint().point() - v0().texturePoint().point()) * centrePointRatio
  );

  /**
  For both top and bottom create two lines (with the same start and end y values) to texture between
  */
  // Texture the top half
  CanvasLine topShortLine = CanvasLine(v0(), v1());
  CanvasLine topHalfLine = CanvasLine(v0(), centerPoint);
  mapTextureBetween2Lines(topShortLine, topHalfLine, texture, window, 0, *this); 
  
  // Texture the bottom half
  CanvasLine bottomShortLine = CanvasLine(v1(), v2());
  CanvasLine bottomHalfLine = CanvasLine(centerPoint, v2());
  mapTextureBetween2Lines(bottomShortLine, bottomHalfLine, texture, window, (int)centerPoint.y(), *this);
}

void CanvasTriangle::draw(Colour &colour, DrawingWindow &window) {
  CanvasLine(v0(), v1()).draw(colour, window);
  CanvasLine(v1(), v2()).draw(colour, window);
  CanvasLine(v2(), v0()).draw(colour, window);
}

void CanvasTriangle::orderVertices() {
  std::sort(std::begin(_vertices), std::end(_vertices), CanvasPointYComparitor);
}

std::ostream &operator<<(std::ostream &os, CanvasTriangle &triangle) {
	os << triangle.v0() << triangle.v1() << triangle.v1();
	return os;
}
