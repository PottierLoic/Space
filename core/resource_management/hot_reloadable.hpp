#pragma once
#include <memory>
#include <string>
#include "resource.hpp"

namespace SpaceEngine {

class IHotReloadable {
public:
  virtual ~IHotReloadable() = default;
  [[nodiscard]] virtual bool isOutdated() const = 0;
  [[nodiscard]] virtual std::shared_ptr<Resource> reload() const = 0;
};

}
