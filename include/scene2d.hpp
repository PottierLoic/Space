#pragma once

#include <vector>
#include <memory>
#include "sceneObject.hpp"
#include "camera.hpp"

class Scene2D {
public:
  /* List of scene objects. */
  std::vector<std::unique_ptr<SceneObject>> objects;

  /* Camera for the scene */
  Camera camera;

  /* Add an object to the scene objects list.
    It must inherit from SceneObject class. */
  void addSceneObject(std::unique_ptr<SceneObject> obj);

  void render(SDL_Renderer *renderer);
};
