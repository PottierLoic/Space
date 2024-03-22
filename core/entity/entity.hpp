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

  /* TODO DOCUMENT */
  static std::shared_ptr<Entity> create(std::string name) {
    auto entity = std::shared_ptr<Entity>(new Entity());
    entity->addComponent<Transform>(name);
    return entity;
  }

  /**
   * Add a given component to the Entity.
   * @tparam T: Type of the component to add.
   * @param component: A pointer to the component to add.
   *
   * @note Declared in .hpp to avoid massive template declaration.
   */
  template <typename T, typename... Args>
  void addComponent(Args&&... args) {
    auto component = std::make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
    components[typeid(T)] = component;
  }

  /**
   * Get a given component from the Entity.
   * @tparam T: Type of the component to get.
   *
   * @note Declared in .hpp to avoid massive template declaration.
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
   *
   * @note Declared in .hpp to avoid massive template declaration.
   */
  template <typename T>
  void removeComponent() {
    auto it = components.find(typeid(T));
    if (it != components.end()) {
      components.erase(it);
    }
  }

  /* WARNING: TODO: Be careful with the two following as they could lead to infinite
    loop on menu display  In case a children contains one of its parent, ImGui will
    never stop and crash.  Prevent this case with check !!!! */

  /**
   * Add a child to children vector of the entity.
   * @param child: A reference to an Entity.
   */
  void addChild(std::unique_ptr<Entity> child);

  // TODO UPDATE AND CHECK IF INDEX IS GOOD
  /**
   * Remove a child from children vector of the entity.
   * @param child: A reference to an Entity.
   */
  void removeChild(int index);
};

}
