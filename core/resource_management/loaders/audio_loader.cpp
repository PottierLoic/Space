#include "audio_loader.hpp"

namespace SpaceEngine {

std::vector<uint8_t> AudioLoader::loadWav(const std::string& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return {};
  }

  file.seekg(0, std::ios::end);
  const std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> buffer(size);

  if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
    return {};
  }

  // TODO: Maybe check wav header?

  return buffer;
}

}