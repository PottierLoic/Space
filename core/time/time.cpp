#include "time.hpp"

namespace SpaceEngine {

std::chrono::steady_clock::time_point Time::s_startTime;
std::chrono::steady_clock::time_point Time::s_lastFrameTime;

float Time::s_time = 0.0f;
float Time::s_deltaTime = 0.0f;
float Time::s_unscaledDeltaTime = 0.0f;
float Time::s_timeScale = 1.0f;

void Time::init() {
  s_startTime = std::chrono::steady_clock::now();
  s_lastFrameTime = s_startTime;
  s_time = 0.0f;
  s_deltaTime = 0.0f;
}

void Time::update() {
  const auto now = std::chrono::steady_clock::now();
  s_unscaledDeltaTime = std::chrono::duration<float>(now - s_lastFrameTime).count();
  s_deltaTime = s_unscaledDeltaTime * s_timeScale;
  s_lastFrameTime = now;
  s_time += s_deltaTime;
}

float Time::deltaTime() {
  return s_deltaTime;
}

float Time::unscaledDeltaTime() {
  return s_unscaledDeltaTime;
}

float Time::time() {
  return s_time;
}

float Time::timeScale() {
  return s_timeScale;
}

void Time::setTimeScale(const float scale) {
  s_timeScale = scale;
}

}
