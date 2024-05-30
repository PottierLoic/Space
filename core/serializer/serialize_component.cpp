#include "serializer/serializer.hpp"

namespace SpaceEngine {

json Serializer::serialize(const Transform& transform) {
  json j;
  j["position"] = { transform.position.x(), transform.position.y(), transform.position.z() };
  j["rotation"] = { transform.rotation.x(), transform.rotation.y(), transform.rotation.z() };
  j["scale"] = { transform.scale.x(), transform.scale.y(), transform.scale.z() };
  return j;
}

}