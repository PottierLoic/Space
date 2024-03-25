#pragma once

#include <string>

#include "component/component.hpp"
#include "vector/vector.hpp"

namespace SpaceEngine {

/**
 * The Transform class represents a transformation component in 3D space, inheriting from Component.
 *
 * Properties:
 * - name (std::string): The name of the object.
 * - position (Vec3d): The position of the transform in 3D space.
 * - rotation (Vec3d): The rotation of the transform in 3D space.
 * - scale (Vec3d): The scale of the transform in 3D space.
 *
 * Methods:
 * - Transform(std::string name): Default constructor: Initializes a new transform component with default values.
 * - ~Transform(): Destructor: Destroys the transform component. Note: May not have additional functionality in this case.
 */
class Transform : public Component {
public:
  std::string name;  /* The name of the object. */
  Vec3d position;  /* The position of the transform in 3D space. */
  Vec3d rotation;  /* The rotation of the transform in 3D space. */
  Vec3d scale;     /* The scale of the transform in 3D space. */

  /**
   * @brief Default constructor: Initializes a new transform component with default values.
   * @param owner (std::weak_ptr<Entity>): A pointer to the entity that store the component.
   * @param name: The name of the object.
   */
  Transform(std::weak_ptr<Entity> owner, std::string name);

};

}