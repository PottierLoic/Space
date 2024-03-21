#include "entity.hpp"

namespace SpaceEngine {

// TODO REMOVE ?
Entity::Entity() {}

void Entity::addChild(std::unique_ptr<Entity> child) {
  children.push_back(std::move(child));
}

void Entity::removeChild(int index) {
  if (index >= 0 && static_cast<std::size_t>(index) < children.size()) {
    children.erase(children.begin() + index);
  } else {
    std::cerr << "Attempted to remove a child with an invalid index: " << index << std::endl;
  }
}

}
