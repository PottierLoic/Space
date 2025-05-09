#include "serializer/serializer.hpp"

namespace SpaceEngine {

std::shared_ptr<Scene> Serializer::deserializeScene(const json &j) {
  auto scene = std::make_shared<Scene>();
  scene->entities.pop_back();
  scene->name = j["name"];
  for (const auto &entityJson : j["entities"]) {
    if (auto entity = deserializeEntity(entityJson)) {
      scene->entities.push_back(entity);
    }
  }
  for (const auto &entity : scene->entities) {
    if (entity->getComponent<Camera>()) {
      scene->selectedCamera = entity->getComponent<Camera>();
      break;
    }
  }
  return scene;
}

std::shared_ptr<Entity> Serializer::deserializeEntity(const json &j) {
  std::shared_ptr<Entity> ent = Entity::createEmpty();
  for (const auto &compJson : j["components"]) {
    if (std::shared_ptr<Component> component = deserializeComponent(compJson)) {
      auto &dereferencedComponent = *component;
      std::type_index typeIndex(typeid(dereferencedComponent));
      ent->components[typeIndex] = component;
    }
  }
  return ent;
}

} // namespace SpaceEngine

