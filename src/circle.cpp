#include "circle.hpp"

Circle::Circle() {
  this->type = ObjectType::CIRCLE;
  this->position = Vector2();
  this->radius = 0;
  this->color = {255, 255, 255, 255};
}

Circle::Circle(Vector2 position, int radius, SDL_Color color) {
  this->type = ObjectType::CIRCLE;
  this->position = position;
  this->radius = radius;
  this->color = color;
}

Circle::Circle(int x, int y, int radius, SDL_Color color) {
  this->type = ObjectType::CIRCLE;
  this->position = Vector2(x, y);
  this->radius = radius;
  this->color = color;
}

