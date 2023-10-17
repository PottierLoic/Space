#include "circle.hpp"

Circle::Circle() {
  this->type = ObjectType::CIRCLE;
  this->x = 0;
  this->y = 0;
  this->radius = 0;
  this->color = {255, 255, 255, 255};
}

Circle::Circle(int x, int y, int radius, SDL_Color color) {
  this->type = ObjectType::CIRCLE;
  this->x = x;
  this->y = y;
  this->radius = radius;
  this->color = color;
}

