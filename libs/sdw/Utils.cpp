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

void drawProgressBar(float progress) {
  int barWidth = 70;

  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
      if (i < pos) std::cout << "=";
      else if (i == pos) std::cout << ">";
      else std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " %\r";
  std::cout.flush();
}

glm::mat3 rotationMatrix(float yaw, float pitch, float roll) {
  return glm::mat3 (
    std::cos(yaw)*std::cos(pitch),                                             std::sin(yaw)*std::cos(pitch),                                             -std::sin(pitch),
    std::cos(yaw)*std::sin(pitch)*std::sin(roll)-std::sin(yaw)*std::cos(roll), std::sin(yaw)*std::sin(pitch)*std::sin(roll)+std::cos(yaw)*std::cos(roll), std::cos(pitch)*std::sin(roll),
    std::cos(yaw)*std::sin(pitch)*std::cos(roll)+std::sin(yaw)*std::sin(roll), std::sin(yaw)*std::sin(pitch)*std::cos(roll)-std::cos(yaw)*std::sin(roll), std::cos(pitch)*std::cos(roll)
  );
}
