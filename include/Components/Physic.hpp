#pragma once

#include "Components/Component.hpp"

class Physic : public Component {
public:
  double mass;          // The mass of the object.
  double drag;          // The resitance applied to the movement.
  double angularDrag;   // The angular resistance applied to rotation.
  bool gravity;         // Affected by gravity if enabled.

  /* Default constructor: Initializes a new physic component with default values. */
  Physic();

  /* Destructor: Destroys the physic component. Note: May not have additional functionality in this case. */
  ~Physic();

  /* Display the physic component properties in the inspector tab. */
  void display() override;
};
