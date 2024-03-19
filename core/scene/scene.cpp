#include "scene.hpp"

namespace SpaceEngine {

Scene::Scene() {
  this->name = "New Scene";
  Entity* defaultCamera = new Entity("Default Camera");
  defaultCamera->addComponent<Camera>();
  this->addEntity(defaultCamera);
  this->selectedCamera = defaultCamera->getComponent<Camera>();
}

void Scene::addEntity(Entity* ent) {
  entities.push_back(ent);
}

void Scene::removeEntity(Entity* ent) {
  entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
}

}
