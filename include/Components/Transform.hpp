#pragma once

#include "Components/Component.hpp"
#include "Vectors/Vector3.hpp"

class Transform : public Component {
public:
  std::string name;  // The name of the object.
  Vector3 position;  // The position of the transform in 3D space.
  Vector3 rotation;  // The rotation of the transform in 3D space.
  Vector3 scale;     // The scale of the transform in 3D space.

  /* Default constructor: Initializes a new transform component with default values. */
  Transform(std::string name);

  /* Destructor: Destroys the transform component. Note: May not have additional functionality in this case. */
  ~Transform();

  /* Display the transform component properties in the inspector tab. */
  void display() override;
};
