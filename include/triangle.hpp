#pragma once

#include <SDL2/SDL.h>
#include "sceneObject.hpp"
#include "vector3.hpp"

class Triangle : public SceneObject {
public:
  Vector3 p1, p2, p3;
  float angle;
  SDL_Color color;

  Triangle(Vector3 p1, Vector3 p2, Vector3 p3, float angle, SDL_Color color);
  void render(SDL_Renderer *renderer) override;
};
