#include "scene.hpp"

namespace SpaceEngine {

Scene::Scene() {
  this->name = "New Scene";
  auto defaultCamera = Entity::create("Default Camera");
  defaultCamera->addComponent<Camera>();
  this->addEntity(defaultCamera);
  this->selectedCamera = defaultCamera->getComponent<Camera>();
}

void Scene::addEntity(std::shared_ptr<Entity> ent) {
  entities.push_back(ent);
}

void Scene::addEntity(std::string name) {
  entities.push_back(Entity::create(name.c_str()));
}

void Scene::removeEntity(int index) {
   if (index >= 0 && static_cast<size_t>(index) < entities.size()) {
    entities.erase(entities.begin() + index);
  } else {
    std::cerr << "Error: Attempted to remove entity with invalid index: " << index << std::endl;
  }
}

}
