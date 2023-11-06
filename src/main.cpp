#define SDL_MAIN_HANDLED

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "eventManager.hpp"
#include "scene2d.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main() {
  SDL_Renderer *renderer;
  SDL_Window *window;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Error initalizing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    return 1;
  }

  EventManager *event_manager = new EventManager();

  Scene2D *scene = new Scene2D();
  scene->addSceneObject(std::make_unique<Circle>(Vector3(100, 100), 50, SDL_Color{255, 0, 0, 255}));
  scene->addSceneObject(std::make_unique<Circle>(Vector3(200, 200), 50, SDL_Color{0, 255, 0, 255}));
  scene->addSceneObject(std::make_unique<Rectangle>(Vector3(400, 100), 100, 100, 0, SDL_Color{255, 0, 0, 255}));
  scene->addSceneObject(std::make_unique<Rectangle>(Vector3(600, 500), 50, 100, 45, SDL_Color{0, 255, 0, 255}));
  scene->addSceneObject(std::make_unique<Triangle>(Vector3(300, 300), Vector3(300, 100), Vector3(500, 300), 0.01, SDL_Color{0, 0, 255, 100}));

  while (!event_manager->quit) {
    event_manager->update();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    scene->render(renderer);

    Rectangle *r = (Rectangle *)scene->objects[3].get();
    r->angle += 0.01;

    Triangle *t = (Triangle *)scene->objects[4].get();
    t->angle += 0.01;


    SDL_RenderPresent(renderer);
  }

  delete event_manager;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
