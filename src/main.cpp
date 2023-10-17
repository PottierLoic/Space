#define SDL_MAIN_HANDLED

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "renderer2D.hpp"
#include "eventManager.hpp"
#include "scene.hpp"
#include "circle.hpp"

int main() {
  Renderer2D *renderer2d = new Renderer2D();
  EventManager *event_manager = new EventManager();
  Scene *scene = new Scene();
  scene->addSceneObject(std::make_unique<Circle>(100, 100, 50, SDL_Color{255, 0, 0, 255}));
  scene->addSceneObject(std::make_unique<Circle>(200, 200, 50, SDL_Color{0, 255, 0, 255}));
  scene->addSceneObject(std::make_unique<Rect>(100, 100, 100, 100, 0, SDL_Color{255, 0, 0, 255}));
  scene->addSceneObject(std::make_unique<Rect>(200, 200, 100, 100, 45, SDL_Color{0, 255, 0, 255}));

  while (!event_manager->quit) {
    event_manager->update();
    SDL_SetRenderDrawColor(renderer2d->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer2d->renderer);

    renderer2d->draw_scene(scene);

    SDL_RenderPresent(renderer2d->renderer);
  }

  delete renderer2d;
  delete event_manager;
  return EXIT_SUCCESS;
}

