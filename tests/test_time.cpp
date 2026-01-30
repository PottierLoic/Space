#include <thread>

#include "test.hpp"
#include "time/time.hpp"

using namespace SpaceEngine;

int testTime() {
  Time::init();
  Time::setTimeScale(0.42f);
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  Time::update();
  const float deltaTime = Time::deltaTime();
  const float unscaledDeltaTime = Time::unscaledDeltaTime();
  const float expected = unscaledDeltaTime * 0.42f;

  constexpr float epsilon = 0.001f;
  custom_assert(std::abs(deltaTime - expected) < epsilon,
                "deltaTime (" << deltaTime << ") != unscaledDeltaTime * scale (" << expected
                              << ")");
  return 0;
}
