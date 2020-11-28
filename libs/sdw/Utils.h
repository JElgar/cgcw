#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

std::vector<std::string> split(const std::string &line, char delimiter);
std::vector<float> interpolate(float from, float to, int numberOfValues);
std::vector<glm::vec3> interpolate(glm::vec3 from, glm::vec3 to, int numberOfValues);
std::vector<glm::vec2> interpolate(glm::vec2 from, glm::vec2 to, int numberOfValues);
bool inRange(float inValue, float bound1, float bound2);
