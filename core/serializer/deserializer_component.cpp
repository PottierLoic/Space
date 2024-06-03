#include "serializer/serializer.hpp"

namespace SpaceEngine {

std::unordered_map<std::string, std::function<std::shared_ptr<Component>(const json&)>> Serializer::deserializers = []() {
  std::unordered_map<std::string, std::function<std::shared_ptr<Component>(const json&)>> m;
  m["Transform"] = [](const json& j) -> std::shared_ptr<Component> {
    auto tf = std::make_shared<Transform>(j["name"]);
    tf->position = Vec3f(j["position"][0], j["position"][1], j["position"][2]);
    tf->rotation = Vec3f(j["rotation"][0], j["rotation"][1], j["rotation"][2]);
    tf->scale = Vec3f(j["scale"][0], j["scale"][1], j["scale"][2]);
    return tf;
  };
  m["Camera"] = [](const json& j) -> std::shared_ptr<Component> {
    auto cam = std::make_shared<Camera>();
    cam->front = glm::vec3(j["front"][0], j["front"][1], j["front"][2]);
    cam->up = glm::vec3(j["up"][0], j["up"][1], j["up"][2]);
    cam->right = glm::vec3(j["right"][0], j["right"][1], j["right"][2]);
    cam->worldUp = glm::vec3(j["worldUp"][0], j["worldUp"][1], j["worldUp"][2]);
    cam->yaw = j["yaw"].get<float>();
    cam->pitch = j["pitch"].get<float>();
    cam->zoom = j["zoom"].get<float>();
    cam->skyboxColor = ImVec4(j["skyboxColor"][0], j["skyboxColor"][1], j["skyboxColor"][2], j["skyboxColor"][3]);
    return cam;
  };
  // TODO: Add other deserializers for all components.
  return m;
}();

std::shared_ptr<Component> Serializer::deserializeComponent(const json& j) {
  std::string type = j["type"];
  auto it = deserializers.find(type);
  if (it != deserializers.end()) {
    return it->second(j);
  } else {
    // TODO: create a log entry maybe ?
    std::cerr << "Unknown or missing component type '" << type << "' encountered during deserialization." << std::endl;
  }
  return nullptr;
}

}