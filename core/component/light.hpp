#pragma once

#include "component/component.hpp"
#include "maths/vector.hpp"

namespace SpaceEngine {

enum LightType {
  POINT,
  DIRECTIONAL,
  SPOT
};

class Light final : public Component {
public:
  // General attributes
  float intensity = 1.0f;
  float range = 100.0f;
  // TODO: implement a Color class maybe ?
  // Vector4 color = ...
  float temperature = 1.0f;

  // Specific attributes
  LightType type;
  Vec3f direction;
  float spotAngle{};

  /**
   * @brief Default constructor: Initializes a new Light component with default values.
   */
  Light();

};

}
