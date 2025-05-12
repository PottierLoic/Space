#include <thread>

#include "test.hpp"
#include "time/time.hpp"

using namespace SpaceEngine;

int testTime() {
  Time::init();
  Time::setTimeScale(0.5f);
  Time::update();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  Time::update();
  const float deltaTime = Time::deltaTime();
  custom_assert(deltaTime >= 0.040f && deltaTime <= 0.060f, "Delta time is out of expected range: " << deltaTime);
  const float unscaledDeltaTime = Time::unscaledDeltaTime();
  custom_assert(unscaledDeltaTime >= 0.090f && unscaledDeltaTime <= 0.12f, "Unscaled delta time is out of expected range: " << unscaledDeltaTime);
  return 0;
}
