#include "rect.h"

Rect::Rect(int x, int y, int w, int h, float angle, SDL_Color color) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->angle = angle;
  this->color = color;
}