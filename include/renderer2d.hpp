#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

#include "constants.hpp"
#include "scene.hpp"

/* 2D Shapes */
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

class Renderer2D {
public:
  SDL_Window *window;
  SDL_Renderer *renderer;

  /* Default constructor. Will create everything needed. */
  Renderer2D();

  /* Constructor using an existing SDL_Window and SDL_Renderer */
  Renderer2D(SDL_Window *window, SDL_Renderer *renderer);

  /* Initialize the window / renderer. */
  bool init();

  /* Cleaner */
  ~Renderer2D();

  /* Draw a pixel on the screen. */
  void draw_pixel(int x, int y, SDL_Color color);

  /* Draw an entire scene and it's objects on the screen. */
  void draw_scene(Scene *scene);

  /* Draw a rectangle on the screen. */
  void draw_rectangle(Rectangle *rect);

  /* Draw a circle on the screen. */
  void draw_circle(Circle *circle);

  /* Draw a triangle on the screen. */
  void draw_triangle(Triangle *triangle);
};

#endif