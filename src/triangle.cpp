#include "triangle.hpp"

Triangle::Triangle(Vector2 p1, Vector2 p2, Vector2 p3, float angle, SDL_Color color) {
  this->type = ObjectType::TRIANGLE;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->angle = angle;
  this->color = color;
}

void Triangle::render(SDL_Renderer *renderer) {
  Vector2 center = Vector2((this->p1.x + this->p2.x + this->p3.x) / 3,
                            (this->p1.y + this->p2.y + this->p3.y) / 3);

  // // rotate this around the center by angle
  // Vector2 p1_rotated = Vector2((this->p1.x - center.x) * cos(this->angle) - (this->p1.y - center.y) * sin(this->angle) + center.x,
  //                      (this->p1.x - center.x) * sin(this->angle) + (this->p1.y - center.y) * cos(this->angle) + center.y);

  // Vector2 p2_rotated = Vector2((this->p2.x - center.x) * cos(this->angle) - (this->p2.y - center.y) * sin(this->angle) + center.x,
  //                       (this->p2.x - center.x) * sin(this->angle) + (this->p2.y - center.y) * cos(this->angle) + center.y);

  // Vector2 p3_rotated = Vector2((this->p3.x - center.x) * cos(this->angle) - (this->p3.y - center.y) * sin(this->angle) + center.x,
  //                       (this->p3.x - center.x) * sin(this->angle) + (this->p3.y - center.y) * cos(this->angle) + center.y);

  Vector2 p1_rotated = this->p1;
  Vector2 p2_rotated = this->p2;
  Vector2 p3_rotated = this->p3;

  // double min_x = std::min(p1_rotated.x, std::min(p2_rotated.x, p3_rotated.x));
  // double max_x = std::max(p1_rotated.x, std::max(p2_rotated.x, p3_rotated.x));

  // double min_y = std::min(p1_rotated.y, std::min(p2_rotated.y, p3_rotated.y));
  // double max_y = std::max(p1_rotated.y, std::max(p2_rotated.y, p3_rotated.y));

  for (int x = 0; x <= 100; x++) {
    for (int y = 0; y <= 100; y++) {
      double apx = x - p1_rotated.x;
      double apy = y - p1_rotated.y;

      double bpx = p2_rotated.x - p1_rotated.x;
      double bpy = p2_rotated.y - p1_rotated.y;

      double cpx = p3_rotated.x - p1_rotated.x;
      double cpy = p3_rotated.y - p1_rotated.y;

      double cpa = apx * bpy - apy * bpx;
      double cpb = bpx * cpy - bpy * cpx;
      double cpc = cpx * apy - cpy * apx;

      bool da = (cpa > 0);
      bool db = (cpb > 0);
      bool dc = (cpc > 0);

      if (da == db && db == dc) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}