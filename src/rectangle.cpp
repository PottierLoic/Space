#include "rectangle.hpp"

Rectangle::Rectangle(Vector2 position, int width, int height, float angle, SDL_Color color) {
  this->type = ObjectType::RECT;
  this->position = position;
  this->width = width;
  this->height = height;
  this->angle = angle;
  this->color = color;
}

Rectangle::Rectangle(int x, int y, int width, int height, float angle, SDL_Color color) {
  this->type = ObjectType::RECT;
  this->position = Vector2(x, y);
  this->width = width;
  this->height = height;
  this->angle = angle;
  this->color = color;
}