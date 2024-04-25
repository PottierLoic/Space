#pragma once

#include "maths/vector.hpp"

#include <queue>

namespace SpaceEngine {

class InputManager {
private:
  // Absolute states of keyboard and mouse
  Vec2f mousePosition;
  bool mouseButtons[3] = {false};
  bool keys[1024] = {false};
  int mouseWheelDelta = 0;

  // Dragging states
  bool drag = false;
  Vec2f dragOrigin;
  Vec2f dragCurrent;

  // Complete inputs buffer
  std::queue<int> inputBuffer;

  InputManager() = default;
public:

  // Singleton
  static InputManager& getInstance();

  void update();

  void keyCallback(int key, int scancode, int action, int mods);
  void mouseButtonCallback(int button, int action, int mods);
  void mousePositionCallback(double xpos, double ypos);
  void mouseWheelCallback(double xoffset, double yoffset);

  bool isKeyPressed(int key) const;
  bool isMousePressed(int button) const;
  Vec2f getMousePosition() const;
  int getMouseWheelDelta() const;

  bool isDragging() const;
  Vec2f getDragOrigin() const;
  Vec2f getDragCurrent() const;
};

}