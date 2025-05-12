#pragma once

namespace SpaceEngine {

class Time {
public:
  static void update(float currentTime);
  static void setTimeScale(float scale);

  static float deltaTime();
  static float fixedDeltaTime();
  static float time();
  static float unscaledDeltaTime();
  static float timeScale();

private:
  static float s_currentTime;
  static float s_lastFrameTime;
  static float s_deltatTime;
  static float s_time;
  static float s_timeScale;
};

}
