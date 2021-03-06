#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

std::vector<std::string> split(const std::string &line, char delimiter);
bool inRange(float inValue, float bound1, float bound2);

void drawProgressBar(float progress);
void saveVectorToFile(std::vector<uint32_t> vector, std::string filename);
std::vector<uint32_t> readVectorFromFile(std::string filename);
glm::mat3 rotationMatrix(float yaw, float pitch, float roll);

template <class T> std::vector<T> interpolate(T from, T to, int numberOfValues) {

  std::vector<T> results;
  if (numberOfValues == 1) {
	  results.push_back(from);
	  return results;
  }
  
  T interval = (to-from) / (float)(numberOfValues-1);
  for (float i = 0; i < numberOfValues; i++) {
	  results.push_back(from + interval*i);
  }
  return results;
}
