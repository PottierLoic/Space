#pragma once

#include "resource_management/resource.hpp"
#include "resource_management/loaders/audio_loader.hpp"
#include <string>
#include <memory>
#include <vector>

namespace SpaceEngine {

class ResAudio final : public Resource {
public:
  ResAudio(std::string name, std::vector<uint8_t> data);
  [[nodiscard]] const std::string& getName() const override;
  [[nodiscard]] const std::vector<uint8_t>& getData() const;

  static std::shared_ptr<ResAudio> loadFromFile(const std::string& path);

private:
  std::string m_name;
  std::vector<uint8_t> m_data;
};

}
