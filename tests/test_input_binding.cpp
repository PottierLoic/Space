#include "test.hpp"
#include "input/input.hpp"

using namespace SpaceEngine;

int testInputBinding() {
  int keyCallCount = 0;
  int mouseCallCount = 0;
  int onceCallCount = 0;

  // Bind to key
  const auto keyId = Input::bindKey(KeyCode::A, [&]() { keyCallCount++; }, -1, InputEventType::OnPress);
  Input::simulateKey(KeyCode::A);
  custom_assert(keyCallCount == 1, "Key binding did not trigger");

  // Bind to mouse button
  const auto mouseId = Input::bindMouseButton(MouseButton::Left, [&]() { mouseCallCount++; }, -1, InputEventType::OnPress);
  Input::simulateMouseButton(MouseButton::Left);
  custom_assert(mouseCallCount == 1, "Mouse binding did not trigger");

  // Bind once
  Input::bindKey(KeyCode::B, [&]() { onceCallCount++; }, 1, InputEventType::OnPress);
  Input::simulateKey(KeyCode::B);
  Input::simulateKey(KeyCode::B);
  custom_assert(onceCallCount == 1, "Binding with 1 remainingCalls triggered more than once");

  // Disable binding
  Input::disableBinding(keyId);
  Input::simulateKey(KeyCode::A);
  custom_assert(keyCallCount == 1, "Disabled binding should not trigger");

  // Enable again
  Input::enableBinding(keyId);
  Input::simulateKey(KeyCode::A);
  custom_assert(keyCallCount == 2, "Enabled binding did not trigger again");

  // Unbind by ID
  Input::unbind(mouseId);
  Input::simulateMouseButton(MouseButton::Left);
  custom_assert(mouseCallCount == 1, "Unbound mouse binding should not trigger");

  // Unbind by key
  Input::unbindKey(KeyCode::A);
  Input::simulateKey(KeyCode::A);
  custom_assert(keyCallCount == 2, "Unbound key binding should not trigger");

  // Rebind for clearing tests
  Input::bindKey(KeyCode::C, [&]() { keyCallCount++; }, -1, InputEventType::OnPress);
  Input::bindMouseButton(MouseButton::Right, [&]() { mouseCallCount++; }, -1, InputEventType::OnPress);
  Input::clearKeyBindings();
  Input::clearMouseButtonBindings();
  Input::simulateKey(KeyCode::C);
  custom_assert(keyCallCount == 2, "Key bindings should have been cleared");
  Input::simulateMouseButton(MouseButton::Right);
  custom_assert(mouseCallCount == 1, "Mouse bindings should have been cleared");

  // Final cleanup
  Input::bindKey(KeyCode::D, [&]() { keyCallCount++; }, -1, InputEventType::OnPress);
  Input::bindMouseButton(MouseButton::Button4, [&]() { mouseCallCount++; }, -1, InputEventType::OnPress);
  Input::clearAllBindings();
  Input::simulateKey(KeyCode::D);
  custom_assert(keyCallCount == 2, "All bindings should have been cleared");
  Input::simulateMouseButton(MouseButton::Button4);
  custom_assert(mouseCallCount == 1, "All bindings should have been cleared");

  return 0;
}
