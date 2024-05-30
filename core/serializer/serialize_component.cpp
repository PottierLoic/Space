#include "serializer/serializer.hpp"

namespace SpaceEngine {

json Serializer::serialize(const std::shared_ptr<Component> component) const {
  json j;
  // TODO: fill this
  return j;
}

json Serializer::serialize(const std::shared_ptr<Transform> transform) const {
  json j;
  j["name"] = transform->name;
  j["position"] = { transform->position.x(), transform->position.y(), transform->position.z() };
  j["rotation"] = { transform->rotation.x(), transform->rotation.y(), transform->rotation.z() };
  j["scale"] = { transform->scale.x(), transform->scale.y(), transform->scale.z() };
  return j;
}

}
