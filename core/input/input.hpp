#pragma once

#include "keycodes.def"
#include "mouse_buttons.def"
#include "log/logger.hpp"

#include <unordered_map>
#include <array>
#include <functional>

#include "binding.hpp"
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

/**
 * Input class handles keyboard and mouse state tracking and input bindings.
 * Provides per-frame update and access to current input status, as well as
 * support for callback bindings to key or mouse events.
 */
class Input {
public:

  /**
   * Initialize the Input system with the given GLFW window.
   * @param window: A pointer to the GLFW window.
   */
  static void init(GLFWwindow* window);

  /**
   * Update the current and previous state of inputs.
   * Is called once per frame.
   */
  static void update();

  /**
   * Check if a key is currently being pressed.
   * @param key: The key to check.
   * @return True if the key is pressed, false otherwise.
   */
  static bool isKeyPressed(KeyCode key);

  /**
   * Check if a key was just pressed during the current frame.
   * @param key: The key to check.
   * @return True if the key was just pressed, false otherwise.
   */
  static bool isKeyJustPressed(KeyCode key);

  /**
   * Check if a key was just released during the current frame.
   * @param key: The key to check.
   * @return True if the key was just released, false otherwise.
   */
  static bool isKeyReleased(KeyCode key);

  /**
   * Check if a mouse button is currently being pressed.
   * @param button: The mouse button to check.
   * @return True if the button is pressed, false otherwise.
   */
  static bool isMouseButtonPressed(MouseButton button);

  /**
   * Check if a mouse button was just pressed during the current frame.
   * @param button: The mouse button to check.
   * @return True if the button was just pressed, false otherwise.
   */
  static bool isMouseButtonJustPressed(MouseButton button);

  /**
   * Check if a mouse button was just released during the current frame.
   * @param button: The mouse button to check.
   * @return True if the button was just released, false otherwise.
   */
  static bool isMouseButtonReleased(MouseButton button);

  /**
   * Get the current mouse X position.
   * @return The horizontal mouse position in window coordinates.
   */
  static float getMouseX();

  /**
   * Get the current mouse Y position.
   * @return The vertical mouse position in window coordinates.
   */
  static float getMouseY();

  /**
   * Get the horizontal mouse movement since the last frame.
   * @return The delta X of the mouse.
   */
  static float getMouseDeltaX();

  /**
   * Get the vertical mouse movement since the last frame.
   * @return The delta Y of the mouse.
   */
  static float getMouseDeltaY();

  /**
   * Get the accumulated scroll offset.
   * @return The current scroll value.
   */
  static float getScroll();

  /**
   * Get the scroll change since the last frame.
   * @return The scroll delta value.
   */
  static float getScrollDelta();

  /**
   * Get and consume the scroll delta value.
   * @note This should be used instead of the basic getScrollDelta.
   * @return The scroll delta value.
   */
  static float consumeScrollDelta();

  /**
   * Internal handler for scroll input events.
   * @param offset: The scroll offset reported by GLFW.
   */
  static void onScroll(double offset);

  /**
   * Execute the bindings of the specified key
   * @param key: The key to simulate.
   * @param type: The event type to simulate.
   */
  static void simulateKey(KeyCode key, InputEventType type = InputEventType::OnPress);

  /**
   * Execute the bindings of the specified mouse button
   * @param button: The button to simulate.
   * @param type: The event type to simulate.
   */
  static void simulateMouseButton(MouseButton button, InputEventType type = InputEventType::OnPress);

  /**
   * Bind a callback to a key event.
   * @param key: The key to bind.
   * @param callback: Function to call on the event.
   * @param remainingCalls: Number of times the binding should trigger (-1 for infinite).
   * @param type: The input event type (press, release, hold).
   * @param description: A short description of the binding (for debugging/logging).
   * @return The unique ID of the binding.
   */
  static std::size_t bindKey(KeyCode key, std::function<void()> callback, int remainingCalls = -1, InputEventType type = InputEventType::OnHold, const std::string &description = "");

  /**
   * Bind a callback to a mouse button event.
   * @param button: The mouse button to bind.
   * @param callback: Function to call on the event.
   * @param remainingCalls: Number of times the binding should trigger (-1 for infinite).
   * @param type: The input event type (press, release, hold).
   * @param description: A short description of the binding (for debugging/logging).
   * @return The unique ID of the binding.
   */
  static std::size_t bindMouseButton(MouseButton button, std::function<void()> callback, int remainingCalls = -1, InputEventType type = InputEventType::OnHold, const std::string &description = "");

  /**
   * Unbind a specific input callback using its binding ID.
   * @param id: The binding ID to remove.
   */
  static void unbind(std::size_t id);

  /**
   * Unbind all callbacks associated with a specific key.
   * @param key: The key to unbind.
   */
  static void unbindKey(KeyCode key);

  /**
   * Unbind all callbacks associated with a specific mouse button.
   * @param button: The mouse button to unbind.
   */
  static void unbindMouseButton(MouseButton button);

  /**
   * Remove all key bindings from the system.
   */
  static void clearKeyBindings();

  /**
   * Remove all mouse button bindings from the system.
   */
  static void clearMouseButtonBindings();

  /**
   * Remove all bindings, both key and mouse.
   */
  static void clearAllBindings();

  /**
   * Execute all eligible key and mouse callbacks based on input state.
   */
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

  static std::unordered_map<KeyCode, std::vector<Binding>> s_keyBindings;
  static std::unordered_map<MouseButton, std::vector<Binding>> s_mouseBindings;

  static std::size_t s_nextBindingId;
};

}
