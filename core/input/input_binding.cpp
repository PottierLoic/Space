#include "input.hpp"

namespace SpaceEngine {

std::unordered_map<KeyCode, std::vector<std::function<void()>>> Input::s_keyBindings;
std::unordered_map<MouseButton, std::vector<std::function<void()>>> Input::s_mouseBindings;

void Input::bindKey(const KeyCode key, std::function<void()> callback) {
  s_keyBindings[key].emplace_back(std::move(callback));
}

void Input::bindMouseButton(const MouseButton button, std::function<void()> callback) {
  s_mouseBindings[button].emplace_back(std::move(callback));
}

void Input::dispatchBindings() {
  for (const auto& [key, callbacks] : s_keyBindings) {
    if (isKeyPressed(key)) {
      for (const auto& cb : callbacks) cb();
    }
  }

  for (const auto& [button, callbacks] : s_mouseBindings) {
    if (isMouseButtonPressed(button)) {
      for (const auto& cb : callbacks) cb();
    }
  }
}

void Input::unbindKey(const KeyCode key) {
  s_keyBindings.erase(key);
}

void Input::unbindMouseButton(const MouseButton button) {
  s_mouseBindings.erase(button);
}

void Input::clearKeyBindings() {
  s_keyBindings.clear();
}

void Input::clearMouseButtonBindings() {
  s_mouseBindings.clear();
}

void Input::clearAllBindings() {
  s_keyBindings.clear();
  s_mouseBindings.clear();
}

}
