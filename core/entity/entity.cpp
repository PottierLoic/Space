#include "entity/entity.hpp"

namespace SpaceEngine {

void Entity::addChild(std::shared_ptr<Entity> child) {
  children.push_back(std::move(child));
}

std::shared_ptr<Entity> Entity::findChild(std::string name) {
  for (std::shared_ptr<Entity> child : children) {
    if (child->getComponent<Transform>()->name == name) {
      return child;
    }
  }
  return nullptr;
}

void Entity::removeChild(std::string name) {
  auto it = std::remove_if(children.begin(), children.end(),
    [name](const std::shared_ptr<Entity>& child) {
      return child->getComponent<Transform>()->name == name;
    });
  children.erase(it, children.end());
}

}
