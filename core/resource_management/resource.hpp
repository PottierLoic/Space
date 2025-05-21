#pragma once

#include<string>

namespace SpaceEngine {

class Resource {
public:
  virtual ~Resource() = default;
  [[nodiscard]] virtual const std::string& getName() const = 0;
};

}