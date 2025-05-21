#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

namespace SpaceEngine {

class AudioLoader {
public:
  static std::vector<uint8_t> loadWav(const std::string& path);
};

}