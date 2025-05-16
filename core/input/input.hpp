#pragma once

#include "keycodes.def"
#include "mouse_buttons.def"

#include <unordered_map>
#include <array>
#include <functional>

#include "GLFW/glfw3.h"


namespace SpaceEngine {

enum class KeyCode {
  #define DEFINE_ENUM(name, _) name,
    KEYCODES(DEFINE_ENUM)
  #undef DEFINE_ENUM
};

enum class MouseButton {
  #define DEFINE_ENUM(name, _) name,
    MOUSE_BUTTONS(DEFINE_ENUM)
  #undef DEFINE_ENUM
};

class Input {
public:
  static void init(GLFWwindow* window);
  static void update();
  static bool isKeyPressed(KeyCode key);
  static bool isMouseButtonPressed(MouseButton button);

  static float getMouseX();
  static float getMouseY();
  static float getMouseDeltaX();
  static float getMouseDeltaY();
  static float getScroll();
  static float getScrollDelta();
  static float consumeScrollDelta(); // Should be used to avoid multiple effects for one scroll

  static void onScroll(double offset);

  static void bindKey(KeyCode key, std::function<void()> callback);
  static void bindMouseButton(MouseButton button, std::function<void()> callback);
  static void unbindKey(KeyCode key);
  static void unbindMouseButton(MouseButton button);
  static void clearKeyBindings();
  static void clearMouseButtonBindings();
  static void clearAllBindings();
  static void dispatchBindings();

private:
  static GLFWwindow* s_window;

  static std::unordered_map<KeyCode, bool> s_currentKeys;
  static std::unordered_map<KeyCode, bool> s_previousKeys;

  static std::unordered_map<MouseButton, bool> s_currentMouseButtons;
  static std::unordered_map<MouseButton, bool> s_previousMouseButtons;

  static float s_mouseX;
  static float s_mouseY;
  static float s_lastMouseX;
  static float s_lastMouseY;
  static float s_deltaX;
  static float s_deltaY;
  static float s_scroll;
  static float s_scrollDelta;

  static std::unordered_map<KeyCode, std::vector<std::function<void()>>> s_keyBindings;
  static std::unordered_map<MouseButton, std::vector<std::function<void()>>> s_mouseBindings;

};

}
