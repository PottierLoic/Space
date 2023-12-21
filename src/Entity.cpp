#include "Entity.hpp"

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