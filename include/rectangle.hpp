#pragma once

#include <SDL2/SDL.h>
#include "sceneObject.hpp"
#include "vector3.hpp"

class Rectangle : public SceneObject {
public:
  Vector3 position;
  int width, height;
  float angle;
  SDL_Color color;

  Rectangle(Vector3 position, int width, int height, float angle, SDL_Color color);
  Rectangle(int x, int y, int width, int height, float angle, SDL_Color color);
  void render(SDL_Renderer *renderer) override;
};
