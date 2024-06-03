#include "serializer/serializer.hpp"

namespace SpaceEngine {

std::unordered_map<std::type_index, std::function<json(const std::shared_ptr<Component>&)>> Serializer::serializers = []() {
  std::unordered_map<std::type_index, std::function<json(const std::shared_ptr<Component>&)>> m;
  // Transform
  m[std::type_index(typeid(Transform))] = [](const std::shared_ptr<Component>& comp) -> json {
      auto tf = std::static_pointer_cast<Transform>(comp);
      json j;
      j["type"] = "Transform";
      j["name"] = tf->name;
      j["position"] = { tf->position.x(), tf->position.y(), tf->position.z() };
      j["rotation"] = { tf->rotation.x(), tf->rotation.y(), tf->rotation.z() };
      j["scale"] = { tf->scale.x(), tf->scale.y(), tf->scale.z() };
      return j;
  };
  // Camera
   m[std::type_index(typeid(Camera))] = [](const std::shared_ptr<Component>& comp) -> json {
      auto cam = std::static_pointer_cast<Camera>(comp);
      json j;
      j["type"] = "Camera";
      j["front"] = { cam->front.x, cam->front.y, cam->front.z };
      j["up"] = { cam->up.x, cam->up.y, cam->up.z };
      j["right"] = { cam->right.x, cam->right.y, cam->right.z };
      j["worldUp"] = { cam->worldUp.x, cam->worldUp.y, cam->worldUp.z };
      j["yaw"] = cam->yaw;
      j["pitch"] = cam->pitch;
      j["zoom"] = cam->zoom;
      j["skyboxColor"] = { cam->skyboxColor.x, cam->skyboxColor.y, cam->skyboxColor.z, cam->skyboxColor.w };
      return j;
  };
  // TODO: Add other serializers for all components.
  return m;
}();


json Serializer::serialize(const std::shared_ptr<Component> component) {
  auto typeIndex = std::type_index(typeid(*component));
  auto it = serializers.find(typeIndex);
  if (it != serializers.end()) {
    return it->second(component);
  }
  return json{};
}

}
