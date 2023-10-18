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

void Rectangle::render(SDL_Renderer *renderer) {
  if (angle != 0 ) {
    double centerX = position.x + width / 2.0;
    double centerY = position.y + height / 2.0;

    for (int x = position.x; x < position.x + width; x++) {
      for (int y = position.y; y < position.y + height; y++) {
        double relX = x - centerX;
        double relY = y - centerY;
        double rotatedX = relX * cos(angle) - relY * sin(angle) + centerX;
        double rotatedY = relX * sin(angle) + relY * cos(angle) + centerY;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, rotatedX, rotatedY);
      }
    }
  } else {
    for (int x = position.x; x < position.x + width; x++) {
      for (int y = position.y; y < position.y + height; y++) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}