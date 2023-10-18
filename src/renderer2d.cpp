#include "renderer2D.hpp"

bool Renderer2D::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Error initalizing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

Renderer2D::~Renderer2D() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

Renderer2D::Renderer2D() { init(); }

Renderer2D::Renderer2D(SDL_Window *window, SDL_Renderer *renderer) {
  this->window = window;
  this->renderer = renderer;
}

void Renderer2D::draw_pixel(int x, int y, SDL_Color color) {
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoint(renderer, x, y);
}

void Renderer2D::draw_scene(Scene *scene) {
  for (auto &obj : scene->objects) {
    switch (obj->type) {
      case ObjectType::RECT:
        draw_rectangle((Rectangle *)obj.get());
        break;
      case ObjectType::CIRCLE:
        draw_circle((Circle *)obj.get());
        break;
      case ObjectType::TRIANGLE:
        draw_triangle((Triangle *)obj.get());
        break;
    }
  }
}

void Renderer2D::draw_rectangle(Rectangle *rect) {
  if (rect->angle != 0 ) {
    double centerX = rect->position.x + rect->width / 2.0;
    double centerY = rect->position.y + rect->height / 2.0;

    for (int x = rect->position.x; x < rect->position.x + rect->width; x++) {
      for (int y = rect->position.y; y < rect->position.y + rect->height; y++) {
        double relX = x - centerX;
        double relY = y - centerY;

        double rotatedX = relX * cos(rect->angle) - relY * sin(rect->angle) + centerX;
        double rotatedY = relX * sin(rect->angle) + relY * cos(rect->angle) + centerY;

        draw_pixel((int)rotatedX, (int)rotatedY, rect->color);
      }
    }

  } else {
    for (int x = rect->position.x; x < rect->position.x + rect->width; x++) {
      for (int y = rect->position.y; y < rect->position.y + rect->height; y++) {
        draw_pixel(x, y, rect->color);
      }
    }
  }
}

void Renderer2D::draw_circle(Circle *circle) {
  double centerX = circle->position.x;
  double centerY = circle->position.y;

  for (int x = centerX - circle->radius; x <= centerX + circle->radius; x++) {
    for (int y = centerY - circle->radius; y <= centerY + circle->radius; y++) {
      double relX = x - centerX;
      double relY = y - centerY;

      double distance = sqrt(relX * relX + relY * relY);

      if (distance <= circle->radius) {
        draw_pixel(x, y, circle->color);
      }
    }
  }
}

void Renderer2D::draw_triangle(Triangle *triangle) {
  Vector2 center = Vector2((triangle->p1.x + triangle->p2.x + triangle->p3.x) / 3,
                              (triangle->p1.y + triangle->p2.y + triangle->p3.y) / 3);

  // // rotate triangle around the center by angle
  // Vector2 p1_rotated = Vector2((triangle->p1.x - center.x) * cos(triangle->angle) - (triangle->p1.y - center.y) * sin(triangle->angle) + center.x,
  //                      (triangle->p1.x - center.x) * sin(triangle->angle) + (triangle->p1.y - center.y) * cos(triangle->angle) + center.y);

  // Vector2 p2_rotated = Vector2((triangle->p2.x - center.x) * cos(triangle->angle) - (triangle->p2.y - center.y) * sin(triangle->angle) + center.x,
  //                       (triangle->p2.x - center.x) * sin(triangle->angle) + (triangle->p2.y - center.y) * cos(triangle->angle) + center.y);

  // Vector2 p3_rotated = Vector2((triangle->p3.x - center.x) * cos(triangle->angle) - (triangle->p3.y - center.y) * sin(triangle->angle) + center.x,
  //                       (triangle->p3.x - center.x) * sin(triangle->angle) + (triangle->p3.y - center.y) * cos(triangle->angle) + center.y);

  Vector2 p1_rotated = triangle->p1;
  Vector2 p2_rotated = triangle->p2;
  Vector2 p3_rotated = triangle->p3;

  // double min_x = std::min(p1_rotated.x, std::min(p2_rotated.x, p3_rotated.x));
  // double max_x = std::max(p1_rotated.x, std::max(p2_rotated.x, p3_rotated.x));

  // double min_y = std::min(p1_rotated.y, std::min(p2_rotated.y, p3_rotated.y));
  // double max_y = std::max(p1_rotated.y, std::max(p2_rotated.y, p3_rotated.y));

  for (int x = 0; x <= WIDTH; x++) {
    for (int y = 0; y <= HEIGHT; y++) {
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
        draw_pixel(x, y, triangle->color);
      }
    }
  }
}

double map(double value, double start1, double stop1, double start2, double stop2) {
  return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

void Renderer2D::draw_mandelbrot(int maxIterations) {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {

      double a = map(x, 0, WIDTH, -2.5, 1);
      double b = map(y, 0, HEIGHT, -1, 1);

      double ca = a;
      double cb = b;

      int n = 0;

      while (n < maxIterations) {
        double aa = a * a - b * b;
        double bb = 2 * a * b;

        a = aa + ca;
        b = bb + cb;

        if (a + b > 16) {
          break;
        }

        n++;
      }

      int bright = map(n, 0, maxIterations, 0, 255);

      if (n == maxIterations) {
        bright = 0;
      }

      SDL_SetRenderDrawColor(renderer, bright, bright, bright, 255);
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
}

