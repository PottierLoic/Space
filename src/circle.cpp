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

void Circle::render(SDL_Renderer *renderer) {
  double centerX = this->position.x;
  double centerY = this->position.y;

  for (int x = centerX - this->radius; x <= centerX + this->radius; x++) {
    for (int y = centerY - this->radius; y <= centerY + this->radius; y++) {
      double relX = x - centerX;
      double relY = y - centerY;

      double distance = sqrt(relX * relX + relY * relY);

      if (distance <= this->radius) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}