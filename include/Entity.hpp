#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <vector>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Physic.hpp"

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
   */
  template <typename T>
  void addComponent(T* component);

  /*
   * Add a given component to the Entity.
   * @tparam T: Type of the component to get.
   */
  template <typename T>
  T* getComponent() const;

  /* TODO: Add a removeComponent function */

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