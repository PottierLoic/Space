#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>
#include "sceneObject.hpp"

class Rect : public SceneObject {
public:
  int x, y, width, height;
  float angle;
  SDL_Color color;

  Rect(int x, int y, int width, int height, float angle, SDL_Color color);
};

#endif