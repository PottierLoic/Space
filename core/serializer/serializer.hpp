#pragma once

#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "component/transform.hpp"
#include "component/camera.hpp"

namespace SpaceEngine {

class Serializer {
public:
  static json serialize(const Transform& transform);
  static json serialize(const Camera& camera);

  static void deserialize(const json&, Transform& transform);
};

}