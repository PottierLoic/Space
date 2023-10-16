#include "renderer2d.h"

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
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoint(renderer, x, y);
}

void Renderer2D::draw_rect(Rect *rect) {
  if (rect->angle != 0 ) {
    double centerX = rect->x + rect->w / 2.0;
    double centerY = rect->y + rect->h / 2.0;

    for (int x = rect->x; x < rect->x + rect->w; x++) {
      for (int y = rect->y; y < rect->y + rect->h; y++) {
        double relX = x - centerX;
        double relY = y - centerY;

        double rotatedX = relX * cos(rect->angle) - relY * sin(rect->angle) + centerX;
        double rotatedY = relX * sin(rect->angle) + relY * cos(rect->angle) + centerY;

        draw_pixel((int)rotatedX, (int)rotatedY, rect->color);
      }
    }
  } else {
    for (int x = rect->x; x < rect->x + rect->w; x++) {
      for (int y = rect->y; y < rect->y + rect->h; y++) {
        draw_pixel(x, y, rect->color);
      }
    }
  }
}

void Renderer2D::draw_circle(Circle *circle) {
  double centerX = circle->x;
  double centerY = circle->y;

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
