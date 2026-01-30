#pragma once

#include <array>
#include <functional>
#include <ranges>
#include <unordered_map>

#include "GLFW/glfw3.h"
#include "binding.hpp"
#include "keycodes.def"
#include "log/logger.hpp"
#include "mouse_buttons.def"

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
  static bool isKeyJustPressed(KeyCode key);
  static bool isKeyReleased(KeyCode key);
  static bool isMouseButtonPressed(MouseButton button);
  static bool isMouseButtonJustPressed(MouseButton button);
  static bool isMouseButtonReleased(MouseButton button);
  static float getMouseX();
  static float getMouseY();
  static float getMouseDeltaX();
  static float getMouseDeltaY();
  static float getScroll();
  static float getScrollDelta();
  static float consumeScrollDelta();
  static void onScroll(double offset);

  static void simulateKey(KeyCode key, InputEventType type = InputEventType::OnPress);
  static void simulateMouseButton(MouseButton button,
                                  InputEventType type = InputEventType::OnPress);

  static std::size_t bindKey(KeyCode key, std::function<void()> callback, int remainingCalls = -1,
                             InputEventType type = InputEventType::OnHold,
                             const std::string& description = "", bool enabled = true);

  static std::size_t bindMouseButton(MouseButton button, std::function<void()> callback,
                                     int remainingCalls = -1,
                                     InputEventType type = InputEventType::OnHold,
                                     const std::string& description = "", bool enabled = true);

  static void unbind(std::size_t id);
  static void unbindKey(KeyCode key);
  static void unbindMouseButton(MouseButton button);

  static void clearKeyBindings();
  static void clearMouseButtonBindings();
  static void clearAllBindings();
  static void dispatchBindings();

  static void enableBinding(std::size_t id);
  static void disableBinding(std::size_t id);

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

  static std::unordered_map<KeyCode, std::vector<Binding>> s_keyBindings;
  static std::unordered_map<MouseButton, std::vector<Binding>> s_mouseBindings;

  static std::size_t s_nextBindingId;
};

}  // namespace SpaceEngine
