#include "input/input_manager.hpp"
#include <iostream>

namespace SpaceEngine {

// Static member initialization
std::vector<bool> InputManager::tempKeyStates(350, false);
std::vector<bool> InputManager::tempMouseButtonStates(8, false);
std::pair<double, double> InputManager::tempMousePosition = {0.0, 0.0};
std::pair<double, double> InputManager::tempScrollOffset = {0.0, 0.0};

void InputManager::initialize(GLFWwindow* window) {
  this->window = window;
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);

  keyStates.resize(350, false);
  mouseButtonStates.resize(8, false);
}

void InputManager::registerKeyCallback(int key, KeyCallback callback) {
  keyCallbacks[key] = callback;
}

void InputManager::keyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
  if (key >= 0 && key < static_cast<int>(tempKeyStates.size())) {
    if (action == GLFW_PRESS) {
      tempKeyStates[key] = true;
    } else if (action == GLFW_RELEASE) {
      tempKeyStates[key] = false;
    }
  }
}

void InputManager::mouseCallback(GLFWwindow* /*window*/, double xpos, double ypos) {
  tempMousePosition = {xpos, ypos};
}

void InputManager::scrollCallback(GLFWwindow* /*window*/, double xoffset, double yoffset) {
  tempScrollOffset = {xoffset, yoffset};
}

void InputManager::processInput(float deltaTime) {
  keyStates = tempKeyStates;
  mouseButtonStates = tempMouseButtonStates;
  mousePosition = tempMousePosition;
  scrollOffset = tempScrollOffset;

  for (const auto& [key, callback] : keyCallbacks) {
    if (keyStates[key]) {
      callback(deltaTime);
    }
  }
}


bool InputManager::isKeyPressed(int key) {
  if (key >= 0 && key < static_cast<int>(keyStates.size())) {
    return keyStates[key];
  }
  return false;
}

bool InputManager::isMouseButtonPressed(int button) {
  if (button >= 0 && button < static_cast<int>(mouseButtonStates.size())) {
    return mouseButtonStates[button];
  }
  return false;
}

std::pair<double, double> InputManager::getMousePosition() {
  return mousePosition;
}

std::pair<double, double> InputManager::getScrollOffset() {
  return scrollOffset;
}

}
