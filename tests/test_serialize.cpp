#include "test.hpp"
#include "scene/scene.hpp"
#include "entity/entity.hpp"
#include "serializer/serializer.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace SpaceEngine;

int testSerialize() {
  // Only check entities and their component presence and not their values.
  // Values are tested in `test_serialize_component.cpp` instead.
  const auto sc = std::make_shared<Scene>();
  const json j = Serializer::serialize(sc);
  const std::shared_ptr<Scene> sc2 = Serializer::deserializeScene(j);
  const std::shared_ptr<Entity> ent = sc2->entities[0];
  custom_assert(ent != nullptr, "Scene entities deserialization failed");
  custom_assert(ent->getComponent<Transform>() != nullptr, "Scene entities transform deserialization failed");
  custom_assert(ent->getComponent<Camera>() != nullptr, "Scene entities camera deserialization failed");
  return 0;
}
