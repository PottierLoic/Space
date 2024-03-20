#pragma once

#include <string>

#include "component/component.hpp"
#include "vector/vector3.hpp"

namespace SpaceEngine {

/**
 * The Transform class represents a transformation component in 3D space, inheriting from Component.
 *
 * Properties:
 * - name (std::string): The name of the object.
 * - position (Vector3): The position of the transform in 3D space.
 * - rotation (Vector3): The rotation of the transform in 3D space.
 * - scale (Vector3): The scale of the transform in 3D space.
 *
 * Methods:
 * - Transform(std::string name): Default constructor: Initializes a new transform component with default values.
 * - ~Transform(): Destructor: Destroys the transform component. Note: May not have additional functionality in this case.
 */
class Transform : public Component {
public:
  std::string name;  /* The name of the object. */
  Vector3 position;  /* The position of the transform in 3D space. */
  Vector3 rotation;  /* The rotation of the transform in 3D space. */
  Vector3 scale;     /* The scale of the transform in 3D space. */

  /**
   * @brief Default constructor: Initializes a new transform component with default values.
   * @param owner (Entity*): A pointer to the entity that store the component.
   * @param name: The name of the object.
   */
  Transform(Entity* owner, std::string name);

  /**
   * @brief Destructor: Destroys the transform component. Note: May not have additional functionality in this case.
   */
  ~Transform();

};

}