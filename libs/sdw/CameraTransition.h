#pragma once
#include "CameraWayPoint.h"
#include <vector>

class CameraTransition {
  public:
    CameraTransition(std::vector<CameraWayPoint> wayPoints, int startFrame = 0);

    // Total number of frames for this transition
    int frames();
    std::vector<CameraWayPoint> wayPoints();
    int startFrame();

  private:
    std::vector<CameraWayPoint> _wayPoints;
    int _startFrame;
};
