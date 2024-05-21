#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>

namespace SpaceEngine {

class InputManager {
public:
  using KeyCallback = std::function<void(float)>;

  static InputManager& getInstance() {
    static InputManager instance;
    return instance;
  }

  void initialize(GLFWwindow* window);
  void registerKeyCallback(int key, KeyCallback callback);

  void processInput(float deltaTime);

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

  bool isKeyPressed(int key);
  bool isMouseButtonPressed(int button);
  std::pair<double, double> getMousePosition();
  std::pair<double, double> getScrollOffset();

private:
  InputManager() = default;
  GLFWwindow* window;
  std::unordered_map<int, KeyCallback> keyCallbacks;
  std::vector<bool> keyStates;
  std::vector<bool> mouseButtonStates;
  std::pair<double, double> mousePosition;
  std::pair<double, double> scrollOffset;

  static std::vector<bool> tempKeyStates;
  static std::vector<bool> tempMouseButtonStates;
  static std::pair<double, double> tempMousePosition;
  static std::pair<double, double> tempScrollOffset;
};

}
