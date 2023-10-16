#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>

class Rect {
public:
  int x, y, w, h;
  float angle;
  SDL_Color color;

  Rect(int x, int y, int w, int h, float angle, SDL_Color color);
};

#endif