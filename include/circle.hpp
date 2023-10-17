#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include "sceneObject.hpp"

class Circle : public SceneObject {
public:
  int x, y, radius;
  SDL_Color color;

  Circle();
  Circle(int x, int y, int radius, SDL_Color color);
};

#endif