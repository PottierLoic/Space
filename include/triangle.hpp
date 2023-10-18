#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <SDL2/SDL.h>
#include "sceneObject.hpp"
#include "vector2.hpp"

class Triangle : public SceneObject {
public:
  Vector2 p1, p2, p3;
  float angle;
  SDL_Color color;

  Triangle(Vector2 p1, Vector2 p2, Vector2 p3, float angle, SDL_Color color);
  void render(SDL_Renderer *renderer) override;
};

#endif