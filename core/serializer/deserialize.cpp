#include "serializer/serializer.hpp"

namespace SpaceEngine {

std::shared_ptr<Scene> Serializer::deserializeScene(const json& j) {
  std::shared_ptr<Scene> scene = std::make_shared<Scene>();
  scene->entities.pop_back();
  scene->name = j["name"];
  for (const auto& entityJson : j["entities"]) {
    auto entity = deserializeEntity(entityJson);
    if (entity) {
      scene->entities.push_back(entity);
    }
  }
  for (const auto& entity : scene->entities) {
    if (entity->getComponent<Camera>()) {
      scene->selectedCamera = entity->getComponent<Camera>();
      break;
    }
  }
  return scene;
}

std::shared_ptr<Entity> Serializer::deserializeEntity(const json& j) {
  std::shared_ptr<Entity> ent = Entity::createEmpty();
  for (const auto& compJson : j["components"]) {
    std::shared_ptr<Component> component = deserializeComponent(compJson);
    if (component) {
      std::type_index typeIndex(typeid(*component));
      ent->components[typeIndex] = component;
    }
  }
  return ent;
}

}