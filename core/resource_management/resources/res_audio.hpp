#pragma once

#include <filesystem>

#include "resource_management/resource.hpp"
#include "resource_management/hot_reloadable.hpp"
#include "resource_management/loaders/audio_loader.hpp"
#include <string>
#include <memory>
#include <vector>

namespace SpaceEngine {

class ResAudio final : public Resource, public IHotReloadable {
public:
  explicit ResAudio(const std::string& path, std::vector<uint8_t> data);
  static std::shared_ptr<ResAudio> loadFromFile(const std::string& path);

  [[nodiscard]] const std::vector<uint8_t>& getData() const;
  [[nodiscard]] std::shared_ptr<Resource> reload() const override;
  [[nodiscard]] bool isOutdated() const override;

private:
  std::vector<uint8_t> m_data;
  std::filesystem::file_time_type m_timestamp;
};

}
