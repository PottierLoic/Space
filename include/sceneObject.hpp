#pragma once

#include <iostream>
#include <SDL2/SDL.h>


enum ObjectType {
  RECT,
  CIRCLE,
  TRIANGLE
};

class SceneObject {
public:
  ObjectType type;

  virtual ~SceneObject();
  virtual void render(SDL_Renderer *renderer);
};
