#include "Entity.hpp"

Entity::Entity(std::string name) {
  this->addComponent<Transform>(new Transform(name));
}

void Entity::addChildren(Entity* child) {
  childs.push_back(child);
}

void Entity::removeChildren(Entity* child) {
  childs.erase(std::remove(childs.begin(), childs.end(), child), childs.end());
}