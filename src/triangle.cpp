#include "triangle.hpp"

Triangle::Triangle(Vector2 p1, Vector2 p2, Vector2 p3, float angle, SDL_Color color) {
  this->type = ObjectType::TRIANGLE;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->angle = angle;
  this->color = color;
}

//TODO: fix it, doesn't display anything right now
void Triangle::render(SDL_Renderer *renderer) {
  Vector2 center = Vector2((this->p1.x + this->p2.x + this->p3.x) / 3,
                            (this->p1.y + this->p2.y + this->p3.y) / 3);

  // rotate this around the center by angle
  Vector2 p1_rotated = Vector2((this->p1.x - center.x) * cos(this->angle) - (this->p1.y - center.y) * sin(this->angle) + center.x,
                       (this->p1.x - center.x) * sin(this->angle) + (this->p1.y - center.y) * cos(this->angle) + center.y);

  Vector2 p2_rotated = Vector2((this->p2.x - center.x) * cos(this->angle) - (this->p2.y - center.y) * sin(this->angle) + center.x,
                        (this->p2.x - center.x) * sin(this->angle) + (this->p2.y - center.y) * cos(this->angle) + center.y);

  Vector2 p3_rotated = Vector2((this->p3.x - center.x) * cos(this->angle) - (this->p3.y - center.y) * sin(this->angle) + center.x,
                        (this->p3.x - center.x) * sin(this->angle) + (this->p3.y - center.y) * cos(this->angle) + center.y);

  // Vector2 p1_rotated = this->p1;
  // Vector2 p2_rotated = this->p2;
  // Vector2 p3_rotated = this->p3;

  double min_x = std::min(p1_rotated.x, std::min(p2_rotated.x, p3_rotated.x));
  double max_x = std::max(p1_rotated.x, std::max(p2_rotated.x, p3_rotated.x));

  double min_y = std::min(p1_rotated.y, std::min(p2_rotated.y, p3_rotated.y));
  double max_y = std::max(p1_rotated.y, std::max(p2_rotated.y, p3_rotated.y));

  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {

    // double apx = p.getX () - a.getX ();
    // double apy = p.getY () - a.getY ();
    // double bpx = p.getX () - b.getX ();
    // double bpy = p.getY () - b.getY ();
    // double cpx = p.getX () - c.getX ();
    // double cpy = p.getY () - c.getY ();
    // double cpa = apx * bpy - apy * bpx;
    // double cpb = bpx * cpy - bpy * cpx;
    // double cpc = cpx * apy - cpy * apx;
    // boolean da = (cpa > 0);
    // boolean db = (cpb > 0);
    // boolean dc = (cpc > 0);
    // return da == db && db == dc;

      double apx = x - p1_rotated.x;
      double apy = y - p1_rotated.y;

      double bpx = x - p1_rotated.x;
      double bpy = y - p1_rotated.y;

      double cpx = x - p1_rotated.x;
      double cpy = y - p1_rotated.y;

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

  /* Debug: draw triangle points with rotation applied. */
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawPoint(renderer, p1_rotated.x, p1_rotated.y);
  SDL_RenderDrawPoint(renderer, p2_rotated.x, p2_rotated.y);
  SDL_RenderDrawPoint(renderer, p3_rotated.x, p3_rotated.y);

  /* draw lines */
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, p1_rotated.x, p1_rotated.y, p2_rotated.x, p2_rotated.y);
  SDL_RenderDrawLine(renderer, p2_rotated.x, p2_rotated.y, p3_rotated.x, p3_rotated.y);
  SDL_RenderDrawLine(renderer, p3_rotated.x, p3_rotated.y, p1_rotated.x, p1_rotated.y);
}