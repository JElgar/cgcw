#include "CanvasLine.h"
#include "Utils.h"

CanvasLine::CanvasLine() = default;
CanvasLine::CanvasLine(CanvasPoint &v0, CanvasPoint &v1) {
  _v0 = v0;
  _v1 = v1;
}

//CanvasLine::CanvasLine(const TexturePoint &v0, const TexturePoint &v1) {
//  _v0 = CanvasPoint(v0.x, v0.y);
//  _v1 = CanvasPoint(v1.x, v1.y);
//}

void CanvasLine::draw(Colour colour, DrawingWindow &window) {
  std::vector<Colour> colourList = {colour};
  draw(colourList, window);
}
		

bool CanvasLine::isOffScreen(DrawingWindow &window) {

  if (v0().x() >= window.width && v1().x() >= window.width) {
    return true;
  }
  if (v0().x() < 0 && v1().x() < 0) {
    return true;
  }
  if (v0().y() >= window.height && v1().y() >= window.height) {
    return true;
  }
  if (v0().y() < 0 && v1().y() < 0) {
    return true;
  }
  // Here we are not sure whether it is on/off the screen but we dont know for
  // sure its off the screen so we are going to draw it anyway. Interpolating here would probably slow down things maybe?
  return false;
}

void CanvasLine::draw(std::vector<Colour> colourList, DrawingWindow &window) {

  if (isOffScreen(window)) {
    return;
  }

  float distanceX = v1().x() - v0().x();
  float distanceY = v1().y() - v0().y();
  if (int(distanceX) == 0 && int(distanceY) == 0) {
    //std::cout << "WARNING WARNING DRAWING LINE OF LENGTH 0!!!!!" << std::endl;
  } else {

    int numberOfSteps = std::ceil(std::max(std::abs(distanceX), std::abs(distanceY)))+1;
    
    if (numberOfSteps == 1) {
      window.setPixel(v0().x(), v0().y(), v0().z(), colourList[0]);
    }

    std::vector<float> xVals = interpolateSingleFloats(v0().x(), v1().x(), numberOfSteps);
    std::vector<float> yVals = interpolateSingleFloats(v0().y(), v1().y(), numberOfSteps);
    std::vector<float> zVals = interpolateSingleFloats(v0().z(), v1().z(), numberOfSteps);
    bool isXIncreasing = xVals[0] < xVals[1];
    bool isYIncreasing = yVals[0] < yVals[1];
    for (int i = 0; i < numberOfSteps; i++) {
      if (isXIncreasing && (xVals[i] >= window.width)) return;
      if (!isXIncreasing && (xVals[i] < 0)) return;
      if (isYIncreasing && (yVals[i] >= window.height)) return;
      if (!isYIncreasing && (yVals[i] < 0)) return;

      Colour colour;
      if (colourList.size() == 1) {
        colour = colourList[0];
      } else {
        colour = colourList[i];
      }

      window.setPixel(xVals[i], yVals[i], zVals[i], colour);
    }
  }
}

