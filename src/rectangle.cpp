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
    Vector2 center = { position.x + width / 2, position.y + height / 2 };
    Vector2 rotated_points[4] = {
      { position.x, position.y },
      { position.x + width, position.y },
      { position.x + width, position.y + height },
      { position.x, position.y + height }
    };

    for (int i = 0; i < 4; i++) {
      double x = rotated_points[i].x - center.x;
      double y = rotated_points[i].y - center.y;
      double new_x = x * cos(angle) - y * sin(angle) + center.x;
      double new_y = x * sin(angle) + y * cos(angle) + center.y;
      rotated_points[i].x = static_cast<int>(new_x);
      rotated_points[i].y = static_cast<int>(new_y);
    }

    int min_x = rotated_points[0].x;
    int max_x = rotated_points[0].x;
    int min_y = rotated_points[0].y;
    int max_y = rotated_points[0].y;

    for (int i = 1; i < 4; i++) {
      if (rotated_points[i].x < min_x) min_x = rotated_points[i].x;
      if (rotated_points[i].x > max_x) max_x = rotated_points[i].x;
      if (rotated_points[i].y < min_y) min_y = rotated_points[i].y;
      if (rotated_points[i].y > max_y) max_y = rotated_points[i].y;
    }

    for (int x = min_x; x <= max_x; x++) {
      for (int y = min_y; y <= max_y; y++) {
        int cpa = (rotated_points[0].x - x) * (rotated_points[1].y - y) - (rotated_points[0].y - y) * (rotated_points[1].x - x);
        int cpb = (rotated_points[1].x - x) * (rotated_points[2].y - y) - (rotated_points[1].y - y) * (rotated_points[2].x - x);
        int cpc = (rotated_points[2].x - x) * (rotated_points[3].y - y) - (rotated_points[2].y - y) * (rotated_points[3].x - x);
        int cpd = (rotated_points[3].x - x) * (rotated_points[0].y - y) - (rotated_points[3].y - y) * (rotated_points[0].x - x);

        if ((cpa >= 0 && cpb >= 0 && cpc >= 0 && cpd >= 0) || (cpa <= 0 && cpb <= 0 && cpc <= 0 && cpd <= 0)) {
          SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
          SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
          SDL_RenderDrawPoint(renderer, x, y);
        }
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
