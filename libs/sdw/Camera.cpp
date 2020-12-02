#include "Camera.h"


Camera::Camera(float x, float y, float z, float focalLength) {
  _focalLength = focalLength;
  setCameraToWorldMatrix(
    glm::mat4(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      x, y, z, 1
    )
  );
 
  //float fov = 90;
  ////float aspect_ratio = 1;
  //float near = 0.1;
  //float far = 100;
  ////float scale = 1 / tan(fov* 0.5 * M_PI / 180);
  ////_projectionMatrix = glm::mat4(
  ////    scale, 0, 0, 0,
  ////    0, scale, 0, 0,
  ////    0, 0, -far/(far-near), -((far * near) / (far - near)),
  ////    0, 0 , -1, -1
  ////);

  ////float top = tan(glm::radians(fov / 2)) * near;
  ////float right = top * aspect_ratio;
  ////_projectionMatrix = glm::mat4(near / right, 0, 0, 0,
  ////                       0, near / top, 0, 0,
  ////                       0, 0, -(far + near) / (far - near), -1,
  ////                       0, 0, -(2 * far * near) / (far - near), 0);
  //  float scale = 1 / tan(fov* 0.5 * M_PI / 180); 
  //  _projectionMatrix[0][0] = scale; // scale the x coordinates of the projected point 
  //  _projectionMatrix[1][1] = scale; // scale the y coordinates of the projected point 
  //  _projectionMatrix[2][2] = -far / (far - near); // used to remap z to [0,1] 
  //  _projectionMatrix[3][2] = -far * near / (far - near); // used to remap z [0,1] 
  //  _projectionMatrix[2][3] = -1; // set w = -z 
  //  _projectionMatrix[3][3] = 0;
}

//void setProjectionMatrix(float angleOfView, float near, float far) {
//   
//}

void Camera::setCameraToWorldMatrix(glm::mat4 matrix) {
  _cameraToWorldMatrix = matrix;
  _worldToCameraMatrix = glm::inverse(matrix);
}

float Camera::x() {
  return _cameraToWorldMatrix[3][0];
}

float Camera::y() {
  return _cameraToWorldMatrix[3][1];
}

float Camera::z() {
  return _cameraToWorldMatrix[3][2];
}

glm::vec3 Camera::getVec3() {
  return glm::vec3(x(), y(), z());
}

glm::mat4 Camera::getCameraToWorldMatrix() {
  return _cameraToWorldMatrix;
}

glm::mat4 Camera::getWorldToCameraMatrix() {
  return _worldToCameraMatrix;
}

float Camera::getFocalLength() {
  return _focalLength;
}

void Camera::rotate(float yaw, float pitch, float roll) {
  glm::mat4 homoRotMatrix = glm::mat4 (
    std::cos(yaw)*std::cos(pitch),                                             std::sin(yaw)*std::cos(pitch),                                             -std::sin(pitch),               0,
    std::cos(yaw)*std::sin(pitch)*std::sin(roll)-std::sin(yaw)*std::cos(roll), std::sin(yaw)*std::sin(pitch)*std::sin(roll)+std::cos(yaw)*std::cos(roll), std::cos(pitch)*std::sin(roll), 0,
    std::cos(yaw)*std::sin(pitch)*std::cos(roll)+std::sin(yaw)*std::sin(roll), std::sin(yaw)*std::sin(pitch)*std::cos(roll)-std::cos(yaw)*std::sin(roll), std::cos(pitch)*std::cos(roll), 0,
    0,                                                                         0,                                                                         0,                              1
  );
  setCameraToWorldMatrix(_cameraToWorldMatrix * homoRotMatrix);
}

void Camera::translate(float x, float y, float z) {
  glm::mat4 homoTransMatrix = glm::mat4 (
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    x, y, z, 1
  );
  setCameraToWorldMatrix(_cameraToWorldMatrix * homoTransMatrix);
}
