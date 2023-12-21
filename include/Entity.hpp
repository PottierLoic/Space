#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"

class Entity {
public:
  std::map<std::type_index, Component*> components;

  /* Default constructor: Initializes a new Entity with default values. */
  Entity(std::string name);

  template <typename T>
  void addComponent(T* component);

  template <typename T>
  T* getComponent() const;
};