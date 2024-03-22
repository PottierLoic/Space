#pragma once

#include "component/component.hpp"

namespace SpaceEngine {

/**
 * The Physic class represents a component defining physical properties for an object.
 *
 * Properties:
 * - mass (double): The mass of the object.
 * - drag (double): The resistance applied to the movement.
 * - angularDrag (double): The angular resistance applied to rotation.
 * - gravity (bool): Indicates whether the object is affected by gravity when enabled.
 *
 * Methods:
 * - Physic(): Default constructor: Initializes a new Physic component with default values.
 * - ~Physic(): Destructor: Destroys the Physic component. Note: May not have additional functionality in this case.
 */
class Physic : public Component {
public:
  double mass;          /* The mass of the object. */
  double drag;          /* The resistance applied to the movement. */
  double angularDrag;   /* The angular resistance applied to rotation. */
  bool gravity;         /* Indicates whether the object is affected by gravity when enabled. */

  /**
   * @brief Default constructor: Initializes a new Physic component with default values.
   * @param owner (std::weak_ptr<Entity>): A pointer to the entity that store the component.
   */
  Physic(std::weak_ptr<Entity> owner);

};

}