#include "test.hpp"
#include "entity/entity.hpp"
#include "serializer/serializer.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace SpaceEngine;

int testSerializeComponent() {
  std::shared_ptr<Transform> tf = std::make_shared<Transform>(Transform("test-transform"));
  tf->position = Vec3f(1.0, 3.0, 5.0);
  tf->rotation = Vec3f(7.0, 9.0, 11.0);
  tf->scale = Vec3f(12.0, 13.0, 15.0);
  json j = Serializer::serialize(tf);
  std::shared_ptr<Transform> tf2 = std::make_shared<Transform>(Transform("test-transform2"));
  Serializer::deserialize(j, tf2);
  custom_assert(tf->name == tf2->name, "Transform name serialization/deserialization failed")
  custom_assert(tf->position == tf2->position, "Transform position serialization/deserialization failed");
  custom_assert(tf->rotation == tf2->rotation, "Transform rotation serialization/deserialization failed");
  custom_assert(tf->scale == tf2->scale, "Transform scale serialization/deserialization failed");
  return 0;
}
