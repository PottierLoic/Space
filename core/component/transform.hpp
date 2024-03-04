#pragma once

#include "component/component.hpp"
#include "vector/vector3.hpp"

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
 * - void display(): Display the transform component properties in the inspector tab.
 */
class Transform : public Component {
public:
  std::string name;  /* The name of the object. */
  Vector3 position;  /* The position of the transform in 3D space. */
  Vector3 rotation;  /* The rotation of the transform in 3D space. */
  Vector3 scale;     /* The scale of the transform in 3D space. */

  /**
   * @brief Default constructor: Initializes a new transform component with default values.
   * @param name: The name of the object.
   */
  Transform(std::string name);

  /**
   * @brief Destructor: Destroys the transform component. Note: May not have additional functionality in this case.
   */
  ~Transform();

  /**
   * @brief Display the transform component properties in the inspector tab.
   */
  void display() override;
};
