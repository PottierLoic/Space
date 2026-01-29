#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "ecs/entity.hpp"
#include "ecs/world.hpp"
#include "component/transform.hpp"
#include "component/camera.hpp"

namespace SpaceEngine {

class Scene{
public:
  std::string name;

  World world;

  Entity selectedCamera;

  Scene();
};

}
