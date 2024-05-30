#include "serializer/serializer.hpp"

namespace SpaceEngine {

void Serializer::deserialize(const json& j, std::shared_ptr<Transform> transform) {
  if (!transform) {
    transform = std::make_shared<Transform>(j["name"]);
  } else {
    transform->name = j["name"];
  }
  transform->position = Vec3f(j["position"][0], j["position"][1], j["position"][2]);
  transform->rotation = Vec3f(j["rotation"][0], j["rotation"][1], j["rotation"][2]);
  transform->scale = Vec3f(j["scale"][0], j["scale"][1], j["scale"][2]);
}

}
