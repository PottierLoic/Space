#include "sceneObject.hpp"

void SceneObject::render(SDL_Renderer *renderer) {
  std::cout << "Cannot render a SceneObject, use a subclass instead." << renderer << std::endl;
}

SceneObject::~SceneObject() {
  std::cout << "SceneObject destructor called" << std::endl;
}