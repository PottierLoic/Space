#pragma once

#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "scene/scene.hpp"
#include "entity/entity.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"

namespace SpaceEngine {

class Serializer {
public:
  static json serialize(const std::shared_ptr<Scene> scene);
  static json serialize(const std::shared_ptr<Entity> entity);
  static json serialize(const std::shared_ptr<Component> component); // TODO: fill this
  static json serialize(const std::shared_ptr<Transform> transform);

  static void deserialize(const json&, std::shared_ptr<Transform> transform);
};

}
