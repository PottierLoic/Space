#pragma once

#include "vector2.hpp"

class Camera {
public:
  Vector2 position;
  Vector2 size;

  Camera();
  Camera(Vector2 position, Vector2 size);
  void movePosition(Vector2 position);
  void setPosition(Vector2 position);
  void setSize(Vector2 size);
};