#define SDL_MAIN_HANDLED

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "renderer2D.hpp"
#include "eventManager.hpp"
#include "scene.hpp"
#include "vector2.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main() {
  Renderer2D *renderer2d = new Renderer2D();
  EventManager *event_manager = new EventManager();
  Scene *scene = new Scene();
  scene->addSceneObject(std::make_unique<Circle>(Vector2(100, 100), 50, SDL_Color{255, 0, 0, 255}));
  scene->addSceneObject(std::make_unique<Circle>(Vector2(200, 200), 50, SDL_Color{0, 255, 0, 255}));
  scene->addSceneObject(std::make_unique<Rectangle>(Vector2(400, 100), 100, 100, 0, SDL_Color{255, 0, 0, 255}));
  scene->addSceneObject(std::make_unique<Rectangle>(Vector2(600, 500), 50, 100, 45, SDL_Color{0, 255, 0, 255}));
  scene->addSceneObject(std::make_unique<Triangle>(Vector2(100, 400), Vector2(200, 400), Vector2(150, 300), 0, SDL_Color{0, 0, 255, 255}));

  while (!event_manager->quit) {
    event_manager->update();
    SDL_SetRenderDrawColor(renderer2d->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer2d->renderer);

    Rectangle *r1 = (Rectangle *)scene->objects[2].get();
    r1->angle += 0.01;
    Rectangle *r2 = (Rectangle *)scene->objects[3].get();
    r2->angle -= 0.01;
    renderer2d->draw_scene(scene);

    SDL_RenderPresent(renderer2d->renderer);
  }

  delete renderer2d;
  delete event_manager;
  return EXIT_SUCCESS;
}

