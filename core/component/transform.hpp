#pragma once

#include <string>

#include "component/component.hpp"
#include "maths/vector.hpp"

namespace SpaceEngine {

/**
 * The Transform class represents a transformation component in 3D space, inheriting from Component.
 *
 * Properties:
 * - name (std::string): The name of the object.
 * - position (Vec3f): The position of the transform in 3D space.
 * - rotation (Vec3f): The rotation of the transform in 3D space.
 * - scale (Vec3f): The scale of the transform in 3D space.
 *
 * Methods:
 * - Transform(std::string name): Default constructor: Initializes a new transform component with default values.
 * - ~Transform(): Destructor: Destroys the transform component. Note: May not have additional functionality in this case.
 */
class Transform final : public Component {
public:
  std::string name;  /* The name of the object. */
  Vec3f position;  /* The position of the transform in 3D space. */
  Vec3f rotation;  /* The rotation of the transform in 3D space. */
  Vec3f scale;     /* The scale of the transform in 3D space. */

  /**
   * @brief Default constructor: Initializes a new transform component with default values.
   * @param name: The name of the object.
   */
  explicit Transform(const std::string &name);
};

}