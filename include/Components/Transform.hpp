#pragma once

/* Needed to use std::string in ImGui::InputText */
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_stdlib.h"

#include "Components/Component.hpp"
#include "Vectors/Vector3.hpp"

class Transform : public Component {
public:
  std::string name;  // The name of the object.
  Vector3 position;  // The position of the transform in 3D space.
  Vector3 rotation;  // The rotation of the transform in 3D space.
  Vector3 scale;     // The scale of the transform in 3D space.

  /* Default constructor: Initializes a new Transform with default values. */
  Transform(std::string name);

  /* Destructor: Destroys the transform. Note: May not have additional functionality in this case. */
  ~Transform();

  /* Display the transform properties in the inspector tab. */
  void display() override;
};
