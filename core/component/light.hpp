#pragma once

#include "maths/vector.hpp"

namespace SpaceEngine {

enum LightType { POINT, DIRECTIONAL, SPOT };

struct Light {
  float intensity = 1.0f;
  float range = 100.0f;
  // TODO: implement a Color class maybe ?
  float temperature = 1.0f;
  LightType type;
  Vec3f direction;
  float spotAngle{};

  Light();
};

}  // namespace SpaceEngine
