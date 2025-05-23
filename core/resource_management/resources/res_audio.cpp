#include "res_audio.hpp"

namespace SpaceEngine {

ResAudio::ResAudio(const std::string& path, std::vector<uint8_t> data)
  : Resource(path), m_data(std::move(data)) {
  m_timestamp = std::filesystem::last_write_time(getPath());
}

std::shared_ptr<ResAudio> ResAudio::loadFromFile(const std::string& path) {
  auto data = AudioLoader::loadWav(path);
  if (data.empty()) return nullptr;
  return std::make_shared<ResAudio>(path, std::move(data));
}

bool ResAudio::isOutdated() const {
  return std::filesystem::last_write_time(getPath()) != m_timestamp;
}

std::shared_ptr<Resource> ResAudio::reload() const {
  return loadFromFile(getPath());
}

}
