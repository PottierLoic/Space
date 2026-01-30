#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "component/camera.hpp"
#include "component/transform.hpp"
#include "ecs/entity.hpp"
#include "ecs/world.hpp"

namespace SpaceEngine {

class Scene {
 public:
  std::string name;

  World world;

  Entity selectedCamera;

  Scene();
};

}  // namespace SpaceEngine
