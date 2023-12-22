#include "Entity.hpp"

template void Entity::addComponent<Transform>(Transform*);
template Transform* Entity::getComponent<Transform>() const;

Entity::Entity(std::string name) {
  this->addComponent<Transform>(new Transform(name));
}

template <typename T>
void Entity::addComponent(T* component) {
  components[typeid(T)] = component;
}

template <typename T>
T* Entity::getComponent() const {
  auto it = components.find(typeid(T));
  if (it != components.end()) {
    return dynamic_cast<T*>(it->second);
  }
  return nullptr;
}

/* TODO: Add a removeComponent function */

void Entity::addChildren(Entity* child) {
  childs.push_back(child);
}

void Entity::removeChildren(Entity* child) {
  childs.erase(std::remove(childs.begin(), childs.end(), child), childs.end());
}