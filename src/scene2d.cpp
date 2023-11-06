#include "scene2d.hpp"
#include "sceneObject.hpp"

void Scene2D::addSceneObject(std::unique_ptr<SceneObject> obj) {
  objects.push_back(std::move(obj));
}

void Scene2D::render(SDL_Renderer *renderer) {
  for (auto &obj : objects) {
    obj->render(renderer);
  }
}
