#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>

#include "Components/Component.hpp"

class Entity {
public:
  std::map<std::type_index, Component*> components;

  template <typename T>
  void addComponent(T* component);

  template <typename T>
  T* getComponent() const;
};