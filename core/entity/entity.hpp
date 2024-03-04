#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <vector>

#include "component/component.hpp"
#include "component/transform.hpp"
#include "component/physic.hpp"

namespace SpaceEngine {

class Entity {
public:
  /* Map of components an Entity has. */
  std::map<std::type_index, Component*> components;
  /* Vector listing all the children entities. */
  std::vector<Entity*> childs;

  /* Default constructor: Initializes a new Entity with default values. */
  Entity(std::string name);

  /*
   * Add a given component to the Entity.
   * @tparam T: Type of the component to add.
   * @param component: A pointer to the component to add.
   *
   * @note Declared in .hpp to avoid massive template declaration.
   */
  template <typename T>
  void addComponent(T* component) {
    components[typeid(T)] = component;
  }

  /*
   * Get a given component from the Entity.
   * @tparam T: Type of the component to get.
   *
   * @note Declared in .hpp to avoid massive template declaration.
   */
  template <typename T>
  T* getComponent() const {
    auto it = components.find(typeid(T));
    if (it != components.end()) {
      return dynamic_cast<T*>(it->second);
    }
    return nullptr;
  }

  /*
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

  /*
   * Add a child to children vector of the entity.
   * @param child: A reference to an Entity.
   */
  void addChildren(Entity* child);

  /*
   * Remove a child from children vector of the entity.
   * @param child: A reference to an Entity.
   */
  void removeChildren(Entity* child);
};

}
