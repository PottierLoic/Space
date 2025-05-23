#include "input.hpp"

namespace SpaceEngine {

GLFWwindow* Input::s_window = nullptr;

std::unordered_map<KeyCode, bool> Input::s_currentKeys;
std::unordered_map<KeyCode, bool> Input::s_previousKeys;

std::unordered_map<MouseButton, bool> Input::s_currentMouseButtons;
std::unordered_map<MouseButton, bool> Input::s_previousMouseButtons;

std::size_t Input::s_nextBindingId = 0;

float Input::s_mouseX = 0.0f;
float Input::s_mouseY = 0.0f;
float Input::s_lastMouseX = 0.0f;
float Input::s_lastMouseY = 0.0f;
float Input::s_deltaX = 0.0f;
float Input::s_deltaY = 0.0f;
float Input::s_scroll = 0.0f;
float Input::s_scrollDelta = 0.0f;

constexpr auto AllKeys = std::to_array({
  #define KEY_ENTRY(name, glfw) KeyCode::name,
    KEYCODES(KEY_ENTRY)
  #undef KEY_ENTRY
});

constexpr auto AllMouseButtons = std::to_array({
  #define MOUSE_ENTRY(name, glfw) MouseButton::name,
  MOUSE_BUTTONS(MOUSE_ENTRY)
  #undef MOUSE_ENTRY
});


int glfwKeyFromKeyCode(const KeyCode key) {
  switch (key) {
  #define DEFINE_CASE(name, glfw) case KeyCode::name: return glfw;
  KEYCODES(DEFINE_CASE)
  #undef DEFINE_CASE
    default: return GLFW_KEY_UNKNOWN;
  }
}

int glfwButtonFromMouseButton(const MouseButton button) {
  switch (button) {
  #define DEFINE_CASE(name, glfw) case MouseButton::name: return glfw;
  MOUSE_BUTTONS(DEFINE_CASE)
  #undef DEFINE_CASE
    default: return -1;
  }
}

static void glfwScrollCallback(GLFWwindow* /*window*/, const double /*xoffset*/, const double yoffset) {
  Input::onScroll(yoffset);
}

void Input::onScroll(const double offset) {
  s_scrollDelta = static_cast<float>(offset);
  s_scroll += static_cast<float>(offset);
}

void Input::init(GLFWwindow* window) {
  s_window = window;
  glfwSetScrollCallback(window, glfwScrollCallback);
}

void Input::update() {
  s_previousKeys = s_currentKeys;
  s_previousMouseButtons = s_currentMouseButtons;

  for (const auto key : AllKeys) {
    const int glfwKey = glfwKeyFromKeyCode(key);
    s_currentKeys[key] = glfwGetKey(s_window, glfwKey) == GLFW_PRESS;
  }

  for (const auto button : AllMouseButtons) {
    const int glfwButton = glfwButtonFromMouseButton(button);
    s_currentMouseButtons[button] = glfwGetMouseButton(s_window, glfwButton) == GLFW_PRESS;
  }

  s_lastMouseX = s_mouseX;
  s_lastMouseY = s_mouseY;

  double xpos, ypos;
  glfwGetCursorPos(s_window, &xpos, &ypos);
  s_mouseX = static_cast<float>(xpos);
  s_mouseY = static_cast<float>(ypos);

  s_deltaX = s_mouseX - s_lastMouseX;
  s_deltaY = s_lastMouseY - s_mouseY;
}

bool Input::isKeyPressed(const KeyCode key) { return s_currentKeys[key]; }
bool Input::isKeyJustPressed(const KeyCode key) { return s_currentKeys[key] && !s_previousKeys[key]; }
bool Input::isKeyReleased(const KeyCode key) { return !s_currentKeys[key] && s_previousKeys[key]; }
bool Input::isMouseButtonPressed(const MouseButton button) { return s_currentMouseButtons[button]; }
bool Input::isMouseButtonJustPressed(const MouseButton button) { return s_currentMouseButtons[button] && !s_previousMouseButtons[button]; }
bool Input::isMouseButtonReleased(const MouseButton button) { return !s_currentMouseButtons[button] && s_previousMouseButtons[button]; }
float Input::getMouseX() { return s_mouseX; }
float Input::getMouseY() { return s_mouseY; }
float Input::getMouseDeltaX() { return s_deltaX; }
float Input::getMouseDeltaY() { return s_deltaY; }
float Input::getScroll() { return s_scroll; }
float Input::getScrollDelta() { return s_scrollDelta; }

float Input::consumeScrollDelta() {
  const float scrollDelta = s_scrollDelta;
  s_scrollDelta = 0.0f;
  return scrollDelta;
}

}
