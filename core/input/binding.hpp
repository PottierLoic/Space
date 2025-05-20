#pragma once
#include <functional>
#include <string>

namespace SpaceEngine {

enum class InputEventType {
  OnPress,
  OnRelease,
  OnHold
};

struct Binding {
  std::size_t id = 0;
  mutable bool enabled;
  std::string description;
  std::function<void()> callback;
  mutable int remainingCalls = -1;
  InputEventType type = InputEventType::OnPress;
};

}
