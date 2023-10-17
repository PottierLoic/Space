#include "triangle.hpp"

Triangle::Triangle(Vector2 p1, Vector2 p2, Vector2 p3, float angle, SDL_Color color) {
  this->type = ObjectType::TRIANGLE;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->angle = angle;
  this->color = color;
}