#include "Utils.h"

#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

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

bool inRange(float inValue, float bound1, float bound2) {
  return (bound1 <= inValue && bound2 >= inValue) || (bound1 >= inValue && bound2 <= inValue);
}

void saveVectorToFile(std::vector<uint32_t> vector, std::string filename) {
  std::ofstream file(filename.c_str());
  for(uint32_t item: vector) {
    file << item << std::endl;
  }
}

std::vector<uint32_t> readVectorFromFile(std::string filename) {
  std::ifstream file(filename.c_str());

  uint32_t data;
  std::vector<uint32_t> outputVector;
  
  while (file >> data) // loop until end of file
  {
     outputVector.push_back(data);
  }
  
  return outputVector;
}
