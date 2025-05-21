#include "res_audio.hpp"

namespace SpaceEngine {

ResAudio::ResAudio(std::string name, std::vector<uint8_t> data)
  : m_name(std::move(name)), m_data(std::move(data)) {}

const std::string& ResAudio::getName() const {
  return m_name;
}

const std::vector<uint8_t>& ResAudio::getData() const {
  return m_data;
}

std::shared_ptr<ResAudio> ResAudio::loadFromFile(const std::string& path) {
  auto data = AudioLoader::loadWav(path);
  if (data.empty()) return nullptr;
  return std::make_shared<ResAudio>(path, data);
}

}
