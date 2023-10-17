#include "rect.hpp"

Rect::Rect(int x, int y, int width, int height, float angle, SDL_Color color) {
  this->type = ObjectType::RECT;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->angle = angle;
  this->color = color;
}