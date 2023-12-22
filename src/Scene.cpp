#include "Scene.hpp"

Scene::Scene() { this->name = "New Scene"; }
Scene::Scene(std::string name) { this->name = name; }

void Scene::addEntity(Entity* ent) {
  entities.push_back(ent);
}

void Scene::removeEntity(Entity* ent) {
  entities.erase(std::remove(entities.begin(), entities.end(), ent), entities.end());
}
