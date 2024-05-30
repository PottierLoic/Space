#include "serializer/serializer.hpp"

namespace SpaceEngine {

void Serializer::deserialize(const json& j, Transform& transform) {
  transform.position = Vec3f(j["position"][0], j["position"][1], j["position"][2]);
  transform.rotation = Vec3f(j["rotation"][0], j["rotation"][1], j["rotation"][2]);
  transform.scale = Vec3f(j["scale"][0], j["scale"][1], j["scale"][2]);
}

}