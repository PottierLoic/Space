#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "constants.h"
#include "rect.h"
#include "circle.h"

class Renderer2D {
public:
  SDL_Window *window;
  SDL_Renderer *renderer;

  Renderer2D();
  Renderer2D(SDL_Window *window, SDL_Renderer *renderer);
  bool init();
  void destroy();
  ~Renderer2D();

  void draw_pixel(int x, int y, SDL_Color color);
  void draw_rect(Rect *rect);
  void draw_circle(Circle *circle);
};

#endif