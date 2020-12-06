#include "ModelTriangle.h"

ModelTriangle::ModelTriangle() = default;
ModelTriangle::ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2) {
  _vertices = {v0, v1, v2};
  setNormal();
}

CanvasTriangle ModelTriangle::project(DrawingWindow &window, Camera &camera, float scalar) {
  return CanvasTriangle(v0().project(window, camera, scalar), v1().project(window, camera, scalar), v2().project(window, camera, scalar));
}

void ModelTriangle::setMaterial(ObjMaterial &material) {
  _material = material;
}

void ModelTriangle::setNormal() {
  _normal = glm::cross(v1().getVec3() - v0().getVec3(), v2().getVec3() - v0().getVec3());
  _normal = glm::normalize(_normal);
}

void ModelTriangle::fill(Colour &colour, DrawingWindow &window, Camera &camera, float scalar) {
  project(window, camera, scalar).fill(colour, window);
}

void ModelTriangle::texture(TextureMap &texture, DrawingWindow &window, Camera &camera, float scalar) {
  project(window, camera, scalar).mapTexture(texture, window);
}

void ModelTriangle::draw(Colour &colour, DrawingWindow &window, Camera &camera, float scalar) {
  project(window, camera, scalar).draw(colour, window);
}

ModelPoint ModelTriangle::v0() {
	return _vertices[0];
}

ModelPoint ModelTriangle::v1() {
	return _vertices[1];
}

ModelPoint ModelTriangle::v2() {
	return _vertices[2];
}

ObjMaterial ModelTriangle::material() {
	return _material;
}

Colour ModelTriangle::colour() {
  if (_material.isNull()) {
    return DEFAULT_COLOUR;
  }
  return _material.getColour();
}

glm::vec3 ModelTriangle::normal() {
  return _normal;
}

RayTriangleIntersection ModelTriangle::getClosestIntersection(Ray &ray) {
  glm::vec3 e0 = v1().getVec3() - v0().getVec3();
  glm::vec3 e1 = v2().getVec3() - v0().getVec3();
  glm::vec3 SPVector = ray.origin()  - v0().getVec3();
  glm::mat3 DEMatrix(-ray.direction(), e0, e1);
  glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;
  if (possibleSolution[1] > 1 || possibleSolution[1] < 0 || possibleSolution[2] > 1 || possibleSolution[2] < 0 || possibleSolution[1] + possibleSolution[2] > 1) {
    return RayTriangleIntersection();
  }
  glm::vec3 r = v0().getVec3() + (possibleSolution[1] * e0) + (possibleSolution[2] * e1);
  ModelPoint intersectionPoint = ModelPoint(r);
 
  // Intersection in the wrong direction - "Behind the origin"
  if ((intersectionPoint.getVec3().x - ray.origin().x) / ray.direction().x < 0) {
    return RayTriangleIntersection();
  }

  return RayTriangleIntersection(intersectionPoint, possibleSolution[0], *this, ray, possibleSolution[1], possibleSolution[2]);
}


std::ostream &operator<<(std::ostream &os, ModelTriangle triangle) {
	os  << triangle.v0().x() << triangle.v0().y() << triangle.v0().z()
	    << triangle.v1().x() << triangle.v1().y() << triangle.v1().z()
	    << triangle.v2().x() << triangle.v2().y() << triangle.v2().z()
        << std::endl; 
	return os;
}
