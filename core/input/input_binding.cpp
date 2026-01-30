#include "input.hpp"

namespace SpaceEngine {

std::unordered_map<KeyCode, std::vector<Binding>> Input::s_keyBindings;
std::unordered_map<MouseButton, std::vector<Binding>> Input::s_mouseBindings;

std::size_t Input::bindKey(const KeyCode key, std::function<void()> callback,
                           const int remainingCalls, const InputEventType type,
                           const std::string& description, const bool enabled) {
  if (remainingCalls == 0)
    throw std::invalid_argument("[Input] Cannot bind key with 0 remaining calls.");
  Binding binding;
  binding.id = s_nextBindingId++;
  binding.description = description;
  binding.callback = std::move(callback);
  binding.remainingCalls = remainingCalls;
  binding.type = type;
  binding.enabled = enabled;
  s_keyBindings[key].push_back(binding);
  return binding.id;
}

std::size_t Input::bindMouseButton(const MouseButton button, std::function<void()> callback,
                                   const int remainingCalls, const InputEventType type,
                                   const std::string& description, const bool enabled) {
  if (remainingCalls == 0)
    throw std::invalid_argument("[Input] Cannot bind mouse button with 0 remaining calls.");
  Binding binding;
  binding.id = s_nextBindingId++;
  binding.description = description;
  binding.callback = std::move(callback);
  binding.remainingCalls = remainingCalls;
  binding.type = type;
  binding.enabled = enabled;
  s_mouseBindings[button].push_back(binding);
  return binding.id;
}

void Input::dispatchBindings() {
  for (const auto& [key, bindings] : s_keyBindings) {
    for (const auto& binding : bindings) {
      if (!binding.enabled || binding.remainingCalls == 0) continue;
      if (binding.type == InputEventType::OnHold && !isKeyPressed(key)) continue;
      if (binding.type == InputEventType::OnRelease && !isKeyReleased(key)) continue;
      if (binding.type == InputEventType::OnPress && !isKeyJustPressed(key)) continue;
      binding.remainingCalls -= 1;
      try {
        binding.callback();
      } catch (const std::exception& e) {
        Logger::error(std::string("[Input] Exception in key callback: ") + e.what() + "\n" +
                      "std::weak_ptr should be used instead of raw pointers");
      } catch (...) {
        Logger::error("[Input] Unknown exception in key callback.");
      }
      if (binding.remainingCalls == 0) unbind(binding.id);
    }
  }

  for (const auto& [button, bindings] : s_mouseBindings) {
    for (const auto& binding : bindings) {
      if (!binding.enabled || binding.remainingCalls == 0) continue;
      if (binding.type == InputEventType::OnHold && !isMouseButtonPressed(button)) continue;
      if (binding.type == InputEventType::OnRelease && !isMouseButtonReleased(button)) continue;
      if (binding.type == InputEventType::OnPress && !isMouseButtonJustPressed(button)) continue;
      binding.remainingCalls -= 1;
      try {
        binding.callback();
      } catch (const std::exception& e) {
        Logger::error(std::string("[Input] Exception in key callback: ") + e.what() + "\n" +
                      "std::weak_ptr should be used instead of raw pointers");
      } catch (...) {
        Logger::error("[Input] Unknown exception in key callback.");
      }
      if (binding.remainingCalls == 0) unbind(binding.id);
    }
  }
}

void Input::unbind(const size_t id) {
  for (auto& bindings : s_keyBindings | std::views::values) {
    for (auto it = bindings.begin(); it != bindings.end(); ++it) {
      if (it->id == id) {
        bindings.erase(it);
        return;
      }
    }
  }
  for (auto& bindings : s_mouseBindings | std::views::values) {
    for (auto it = bindings.begin(); it != bindings.end(); ++it) {
      if (it->id == id) {
        bindings.erase(it);
        return;
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

void Input::simulateKey(const KeyCode key, const InputEventType type) {
  for (const auto& binding : s_keyBindings[key]) {
    if (!binding.enabled) continue;
    if (binding.type == type) {
      if (binding.remainingCalls == 0) continue;
      binding.callback();
      binding.remainingCalls -= 1;
    }
  }
}

void Input::simulateMouseButton(const MouseButton button, const InputEventType type) {
  for (const auto& binding : s_mouseBindings[button]) {
    if (!binding.enabled) continue;
    if (binding.type == type) {
      if (binding.remainingCalls == 0) continue;
      binding.callback();
      binding.remainingCalls -= 1;
    }
  }
}

void Input::enableBinding(const std::size_t id) {
  for (auto& bindings : s_keyBindings | std::views::values) {
    for (const auto& binding : bindings) {
      if (binding.id == id) {
        binding.enabled = true;
        return;
      }
    }
  }
  for (auto& bindings : s_mouseBindings | std::views::values) {
    for (const auto& binding : bindings) {
      if (binding.id == id) {
        binding.enabled = true;
        return;
      }
    }
  }
}

void Input::disableBinding(const std::size_t id) {
  for (auto& bindings : s_keyBindings | std::views::values) {
    for (const auto& binding : bindings) {
      if (binding.id == id) {
        binding.enabled = false;
        return;
      }
    }
  }
  for (auto& bindings : s_mouseBindings | std::views::values) {
    for (const auto& binding : bindings) {
      if (binding.id == id) {
        binding.enabled = false;
        return;
      }
    }
  }
}

}  // namespace SpaceEngine
