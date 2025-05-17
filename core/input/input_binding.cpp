#include "input.hpp"

namespace SpaceEngine {

std::unordered_map<KeyCode, std::vector<Binding>> Input::s_keyBindings;
std::unordered_map<MouseButton, std::vector<Binding>> Input::s_mouseBindings;


std::size_t Input::bindKey(const KeyCode key, std::function<void()> callback, const int remainingCalls, const InputEventType type, const std::string &description) {
  Binding binding;
  binding.id = s_nextBindingId++;
  binding.description = description;
  binding.callback = std::move(callback);
  binding.remainingCalls = remainingCalls;
  binding.type = type;
  s_keyBindings[key].push_back(binding);
  return binding.id;
}

std::size_t Input::bindMouseButton(const MouseButton button, std::function<void()> callback, const int remainingCalls, const InputEventType type, const std::string &description) {
  Binding binding;
  binding.id = s_nextBindingId++;
  binding.description = description;
  binding.callback = std::move(callback);
  binding.remainingCalls = remainingCalls;
  binding.type = type;
  s_mouseBindings[button].push_back(binding);
  return binding.id;}

void Input::dispatchBindings() {
  for (const auto& [key, bindings] : s_keyBindings) {
    for (const auto& binding : bindings) {
      if (binding.remainingCalls == 0) continue;
      if (binding.type == InputEventType::OnHold && !isKeyPressed(key)) continue;
      if (binding.type == InputEventType::OnRelease && isKeyPressed(key)) continue; // TODO: make a isKeyJustReleased for this
      if (binding.type == InputEventType::OnPress && !isKeyPressed(key)) continue; // TODO: make a isKeyJustPressed for this
      binding.remainingCalls -= 1;
      try {
        binding.callback();
      } catch (const std::exception& e) {
        Logger::error(std::string("[Input] Exception in key callback: ") + e.what() + "\n" + "std::weak_ptr should be used instead of raw pointers");
      } catch (...) {
        Logger::error("[Input] Unknown exception in key callback.");
      }
    }
  }

  for (const auto& [button, bindings] : s_mouseBindings) {
    for (const auto& binding : bindings) {
      if (binding.remainingCalls == 0) continue;
      if (binding.type == InputEventType::OnHold && !isMouseButtonPressed(button)) continue;
      if (binding.type == InputEventType::OnRelease && isMouseButtonPressed(button)) continue; // TODO: make a isButtonJustReleased for this
      if (binding.type == InputEventType::OnPress && !isMouseButtonPressed(button)) continue; // TODO: make a isButtonJustPressed for this
      binding.remainingCalls -= 1;
      try {
        binding.callback();
      } catch (const std::exception& e) {
        Logger::error(std::string("[Input] Exception in key callback: ") + e.what() + "\n" + "std::weak_ptr should be used instead of raw pointers");
      } catch (...) {
        Logger::error("[Input] Unknown exception in key callback.");
      }
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
