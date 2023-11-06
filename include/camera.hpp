#pragma once

#include "vector3.hpp"

class Camera {
public:
  Vector3 position;
  double width;
  double height;

  Camera();
  Camera(Vector3 position, double width, double height);
  void movePosition(Vector3 position);
  void setPosition(Vector3 position);
  void setSize(double width, double height);
};