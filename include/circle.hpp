#pragma once

#include <SDL2/SDL.h>
#include "sceneObject.hpp"
#include "vector2.hpp"

class Circle : public SceneObject {
public:
  Vector2 position;
  int radius;
  SDL_Color color;

  Circle();
  Circle(Vector2 position, int radius, SDL_Color color);
  Circle(int x, int y, int radius, SDL_Color color);
  void render(SDL_Renderer *renderer) override;
};