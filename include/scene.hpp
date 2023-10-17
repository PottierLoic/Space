#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "sceneObject.hpp"

class Scene {
public:
  /* List of scene objects. */
  std::vector<std::unique_ptr<SceneObject>> objects;

  /* Add an object to the scene objects list.
    It must inherit from SceneObject class. */
  void addSceneObject(std::unique_ptr<SceneObject> obj);
};

#endif