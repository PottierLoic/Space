#include "scene.hpp"

namespace SpaceEngine {

Scene::Scene() {
  this->name = "New Scene";
  this->addEntity(new Entity("Default Camera"));
}

void Scene::addEntity(Entity* ent) {
  entities.push_back(ent);
}

void Scene::removeEntity(Entity* ent) {
  entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
}

}
