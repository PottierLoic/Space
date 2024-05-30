#pragma once

#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "component/transform.hpp"
#include "component/camera.hpp"

namespace SpaceEngine {

class Serializer {
public:
  static json serialize(const std::shared_ptr<Transform> transform);
  static void deserialize(const json&, std::shared_ptr<Transform> transform);
};

}