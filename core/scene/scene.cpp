#include "scene.hpp"

namespace SpaceEngine {

Scene::Scene() {
  this->name = "New Scene";
  const auto camera = world.create();
  world.add_component<Transform>(camera, Transform("Default Camera"));
  world.add_component<Camera>(camera, Camera{});
  selectedCamera = camera;
}

}  // namespace SpaceEngine
