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
  LightType type;
  Vector3 direction;
  float intensity = 1.0f;
  // color here

  /**
   * @brief Default constructor: Initializes a new Light component with default values.
   * @param owner (weak_ptr<Entity>): A pointer to the entity that store the component.
   */
  Light(std::weak_ptr<Entity> owner);

};

}
