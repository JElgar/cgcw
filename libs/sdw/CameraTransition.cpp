#include "CameraTransition.h"

CameraTransition::CameraTransition(std::vector<CameraWayPoint> wayPoints, int startFrame) {
  _wayPoints = wayPoints;
  _startFrame = startFrame;
}

int CameraTransition::frames() {
  int frames = 0;
  for (CameraWayPoint wayPoint : _wayPoints) {
    frames += wayPoint.frames();
  }
  return frames;
}

std::vector<CameraWayPoint> CameraTransition::wayPoints() {
  return _wayPoints;
}

int CameraTransition::startFrame() {
  return _startFrame;
}
