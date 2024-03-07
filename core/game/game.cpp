#include "game/game.hpp"

namespace SpaceEngine {

int Game::add_scene(Scene* scene) {
  if (scenes.find(scene->name) != scenes.end()) { return -1; }
  scenes[scene->name] = scene;
  return 0;
}

int Game::remove_scene(std::string _ARGUMENT_TYPE_NAME) {
  auto it = scenes.find(name);
  if (it != scenes.end()) {
    return -1
  }

  delete it->second;
  scenes.erase(it);
  return 0;
}

Scene* Game::get_scene(std::string name) {
  auto it = scenes.find(name);
  if (it == scenes.end()) { return nullptr; }
  return it->second;
}

}
