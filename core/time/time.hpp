#pragma once

#include <chrono>

namespace SpaceEngine {

class Time {
public:
  static void init();
  static void update();
  static void setTimeScale(float scale);

  static float deltaTime();
  static float time();
  static float unscaledDeltaTime();
  static float timeScale();

private:
  static std::chrono::steady_clock::time_point s_startTime;
  static std::chrono::steady_clock::time_point s_lastFrameTime;

  static float s_time;
  static float s_deltaTime;
  static float s_unscaledDeltaTime;
  static float s_timeScale;
};

}
