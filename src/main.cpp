#define SDL_MAIN_HANDLED

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "constants.h"
#include "renderer2d.h"
#include "circle.h"

int main() {
  Renderer2D *renderer2d = new Renderer2D();
  SDL_Event event;

  Circle *circle = new Circle(WIDTH / 2, HEIGHT / 2, 100, {255, 255, 255, 255});

  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
    SDL_SetRenderDrawColor(renderer2d->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer2d->renderer);

    renderer2d->draw_circle(circle);

    SDL_RenderPresent(renderer2d->renderer);
  }

  delete renderer2d;
  return EXIT_SUCCESS;
}

