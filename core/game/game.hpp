#pragma once

#include <map>
#include <string>

#include "scene/scene.hpp"

namespace SpaceEngine {

class Game {
private:
  std::map<std::string, Scene*> scenes;

public:
  int add_scene(Scene* scene);
  int remove_scene(std::string name);
  Scene* get_scene(std::string name);
}

}
