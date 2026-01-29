#pragma once

#include <string>
#include "maths/vector.hpp"

namespace SpaceEngine {

struct Transform {
public:
  std::string name; // TODO stay for now but will be in its own component soon
  Vec3f position;
  Vec3f rotation;
  Vec3f scale;

  explicit Transform(const std::string &name);
};

}