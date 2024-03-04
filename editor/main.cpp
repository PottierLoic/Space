#include <iostream>

#include "vector/vector2.hpp"
#include "menu/menu.hpp"

using namespace SpaceEngine;
using namespace SpaceEditor;

int main() {
  Vector2 position(10.0, 20.0);
  Vector2 velocity(5.0, 3.0);

  Vector2 newPosition = position + velocity;
  std::cout << newPosition.x << newPosition.y << std::endl;
  return 0;
}