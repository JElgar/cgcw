#include <algorithm>
#include <sstream>
#include "Utils.h"

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

std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
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

bool inRange(float inValue, float bound1, float bound2) {
  return (bound1 <= inValue && bound2 >= inValue) || (bound1 >= inValue && bound2 <= inValue);
}
