#include <algorithm>
#include <sstream>
#include "Utils.h"
#include <iostream>

std::vector<std::string> split(const std::string &line, char delimiter) {
	auto haystack = line;
	std::vector<std::string> tokens;
	size_t pos;
	while ((pos = haystack.find(delimiter)) != std::string::npos) {
		tokens.push_back(haystack.substr(0, pos));
		haystack.erase(0, pos + 1);
	}
	// Push the remaining chars onto the vector
	tokens.push_back(haystack);
	return tokens;
}

std::vector<float> interpolate(float from, float to, int numberOfValues) {
	std::vector<float> results;
	if (numberOfValues == 1) {
		results.push_back(from);
		return results;
	}
	float interval = (to - from) / (numberOfValues - 1);
	for (int i = 0; i < numberOfValues; i++) {
		results.push_back(from + i*interval);
	}
	return results;
}


std::vector<glm::vec3> interpolate(glm::vec3 from, glm::vec3 to, int numberOfValues) {

  std::vector<glm::vec3> results;
  if (numberOfValues == 1) {
	  results.push_back(from);
	  return results;
  }
  
  glm::vec3 interval = (to-from) / (float)(numberOfValues-1);
  for (float i = 0; i < numberOfValues; i++) {
	  results.push_back(from + interval*i);
  }
  return results;
}

std::vector<glm::vec2> interpolate(glm::vec2 from, glm::vec2 to, int numberOfValues) {

  std::vector<glm::vec2> results;
  if (numberOfValues == 1) {
	  results.push_back(from);
	  return results;
  }
  glm::vec2 interval = (to-from) / (float)(numberOfValues-1);
  std::cout << interval.x << ", " << interval.y  << std::endl;
  for (float i = 0; i < numberOfValues; i++) {
	  results.push_back(from + interval*i);
  }
  return results;
}

bool inRange(float inValue, float bound1, float bound2) {
  return (bound1 <= inValue && bound2 >= inValue) || (bound1 >= inValue && bound2 <= inValue);
}
