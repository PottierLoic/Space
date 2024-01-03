#pragma once

#include <iostream>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_stdlib.h"

class Component {
public:
  Component();
  virtual ~Component();
  virtual void display();
};
