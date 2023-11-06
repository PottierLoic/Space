#include "triangle.hpp"

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3, float angle, SDL_Color color) {
  this->type = ObjectType::TRIANGLE;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->angle = angle;
  this->color = color;
}

void Triangle::render(SDL_Renderer *renderer) {
  Vector3 center = Vector3((this->p1.x + this->p2.x + this->p3.x) / 3,
                           (this->p1.y + this->p2.y + this->p3.y) / 3);

  Vector3 p1_rotated = Vector3((this->p1.x - center.x) * cos(this->angle) - (this->p1.y - center.y) * sin(this->angle) + center.x,
                               (this->p1.x - center.x) * sin(this->angle) + (this->p1.y - center.y) * cos(this->angle) + center.y);

  Vector3 p2_rotated = Vector3((this->p2.x - center.x) * cos(this->angle) - (this->p2.y - center.y) * sin(this->angle) + center.x,
                               (this->p2.x - center.x) * sin(this->angle) + (this->p2.y - center.y) * cos(this->angle) + center.y);

  Vector3 p3_rotated = Vector3((this->p3.x - center.x) * cos(this->angle) - (this->p3.y - center.y) * sin(this->angle) + center.x,
                               (this->p3.x - center.x) * sin(this->angle) + (this->p3.y - center.y) * cos(this->angle) + center.y);

  double min_x = std::min(p1_rotated.x, std::min(p2_rotated.x, p3_rotated.x));
  double max_x = std::max(p1_rotated.x, std::max(p2_rotated.x, p3_rotated.x));

  double min_y = std::min(p1_rotated.y, std::min(p2_rotated.y, p3_rotated.y));
  double max_y = std::max(p1_rotated.y, std::max(p2_rotated.y, p3_rotated.y));

  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {
      double apx = x - p1_rotated.x;
      double apy = y - p1_rotated.y;

      double bpx = x - p2_rotated.x;
      double bpy = y - p2_rotated.y;

      double cpx = x - p3_rotated.x;
      double cpy = y - p3_rotated.y;

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
