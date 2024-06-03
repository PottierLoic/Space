#include "serializer/serializer.hpp"

namespace SpaceEngine {

json Serializer::serialize(std::shared_ptr<Space> space) {
  json j;
  j["name"] = space->name;
  j["path"] = space->path;
  return j;
}

json Serializer::serialize(std::shared_ptr<Scene> scene) {
  json j;
  j["name"] = scene->name;
  j["entities"] = json::array();
  for (const auto& entity : scene->entities) {
    j["entities"].push_back(serialize(entity));
  }
  return j;
}

json Serializer::serialize(std::shared_ptr<Entity> entity) {
  json j;
  j["components"] = json::array();
  for (const auto& [type, component] : entity->components) {
    j["components"].push_back(serialize(component));
  }
  // TODO: implement children serialization
  return j;
}

}