#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <typeindex>

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
  static json serialize(const std::shared_ptr<Component> component);

  static std::shared_ptr<Scene> deserializeScene(const json& j);
  static std::shared_ptr<Entity> deserializeEntity(const json& j);
  static std::shared_ptr<Component> deserializeComponent(const json& j);

private:
  static std::unordered_map<std::type_index, std::function<json(const std::shared_ptr<Component>&)>> serializers;
  static std::unordered_map<std::string, std::function<std::shared_ptr<Component>(const json&)>> deserializers;
};

}
