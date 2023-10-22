#pragma once

#include <SDL2/SDL.h>
#include "sceneObject.hpp"
#include "vector2.hpp"

class Rectangle : public SceneObject {
public:
  Vector2 position;
  int width, height;
  float angle;
  SDL_Color color;

  Rectangle(Vector2 position, int width, int height, float angle, SDL_Color color);
  Rectangle(int x, int y, int width, int height, float angle, SDL_Color color);
  void render(SDL_Renderer *renderer) override;
};
