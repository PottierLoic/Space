#pragma once

#include <memory>
#include <algorithm>
#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <vector>
#include <utility>

#include "component/component.hpp"
#include "component/transform.hpp"

namespace SpaceEngine {

/**
 * TODO
 */
class Entity : public std::enable_shared_from_this<Entity> {
private:
  /**
   * Default constructor: Initializes a new Entity.
   * @note Only usable by Entity::create function. Should never be used somewhere else.
   */
  Entity() = default;

public:
  /* Map of components an Entity has. */
  std::map<std::type_index, std::shared_ptr<Component>> components;
  /* Vector listing all the children entities. */
  std::vector<std::shared_ptr<Entity>> children;

  /**
   * Entity constructor.
   * @param name: (string) the name of the Entity.
   *
   * @return A shared pointer to the Entity created.
   */
  static std::shared_ptr<Entity> create(std::string name) {
    auto entity = std::shared_ptr<Entity>(new Entity());
    entity->addComponent<Transform>(name);
    return entity;
  }

  /**
   * Entity constructor.
   * Return a no-component Entity. Used for deserialization
   * @note Should only be used in the engine/editor and not in games.
   *
   * @return A shared pointer to the Entity created.
   */
  static std::shared_ptr<Entity> createEmpty() {
    auto entity = std::shared_ptr<Entity>(new Entity());
    return entity;
  }

  /**
   * Add a given component to the Entity.
   * @tparam T: Type of the component to add.
   *
   * @return True if the component is added successfully, false otherwise.
   */
  template <typename T, typename... Args>
  bool addComponent(Args&&... args) {
    std::type_index typeIndex(typeid(T));
    if (components.find(typeIndex) != components.end()) {
      return false;
    }

    std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
    component->setOwner(shared_from_this());
    components[typeIndex] = component;
    return true;
  }

  /**
   * Get a given component from the Entity.
   * @tparam T: Type of the component to get.
   *
   * @return Shared pointer to a component if found, nullptr otherwise.
   */
  template <typename T>
  std::shared_ptr<T> getComponent() const {
    auto it = components.find(typeid(T));
    if (it != components.end()) {
      return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
  }

  /**
   * Remove a given component from the Entity.
   * @tparam T: Type of the component to remove.
   */
  template <typename T>
  void removeComponent() {
    auto it = components.find(typeid(T));
    if (it != components.end()) {
      components.erase(it);
    }
  }

  /**
   * Add a child to children vector of the entity.
   * @param child: A reference to an Entity.
   */
  void addChild(std::shared_ptr<Entity> child);

  /**
   * Find a child in the children list of the entity
   * @param name: (string) The name of the entity to find.
   * @return shared_ptr<Entity>: A shared pointer to the found entity, a nullptr otherwise
  */
  std::shared_ptr<Entity> findChild(std::string name);

  /**
   * Remove a child from the entity children vector.
   * @param name: (string) The name of the entity to remove.
   */
  void removeChild(std::string name);
};

}
