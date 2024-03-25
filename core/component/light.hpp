#pragma once

#include "component/component.hpp"
#include "vector/vector3.hpp"

namespace SpaceEngine {

enum LightType {
  POINT,
  DIRECTIONAL,
  SPOT
};

class Light : public Component {
public:
  // General attributes
  float intensity = 1.0f;
  float range = 100.0f;
  // TODO: implement a Color class maybe ?
  // Vector4 color = ...
  float temperature = 1.0f;

  // Specific attributes
  LightType type;
  Vector3 direction;
  float spotAngle;

  /**
   * @brief Default constructor: Initializes a new Light component with default values.
   * @param owner (weak_ptr<Entity>): A pointer to the entity that store the component.
   */
  Light(std::weak_ptr<Entity> owner);

};

}
