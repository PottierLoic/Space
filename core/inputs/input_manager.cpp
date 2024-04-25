#include "inputs/input_manager.hpp"

namespace SpaceEngine {

InputManager& InputManager::getInstance() {
  static InputManager instance;
  return instance;
}

bool InputManager::isKeyPressed(int key) const {
  return keys[key];
}

bool InputManager::isMousePressed(int button) const {
  return mouseButtons[button];
}

Vec2f InputManager::getMousePosition() const {
  return mousePosition;
}

int InputManager::getMouseWheelDelta() const {
  return mouseWheelDelta;
}

bool InputManager::isDragging() const {
  return drag;
}

Vec2f InputManager::getDragOrigin() const {
  return dragOrigin;
}

Vec2f InputManager::getDragCurrent() const {
  return dragCurrent;
}

}