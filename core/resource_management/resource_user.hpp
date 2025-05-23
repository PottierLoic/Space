#pragma once
#include <string>

namespace SpaceEngine {

class IResourceUser {
public:
  virtual ~IResourceUser() = default;
  virtual void onResourceReloaded(const std::string& path) = 0;
};

}
