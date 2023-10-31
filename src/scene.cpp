#include "scene.hpp"
#include "sceneObject.hpp"

void Scene::addSceneObject(std::unique_ptr<SceneObject> obj) {
  objects.push_back(std::move(obj));
}

void Scene::render(SDL_Renderer *renderer) {
  for (auto &obj : objects) {
    obj->render(renderer);
  }
}
