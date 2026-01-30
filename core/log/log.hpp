#pragma once

#include <array>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

namespace SpaceEngine {

enum LogLevel { DEBUG, INFORMATION, WARNING, ERROR, FATAL };

enum LogType { None, Core, Rendering, Audio, Input, Editor, Scripting, AssetLoading };

inline constexpr std::array<const char*, 5> logLevels = {"DEBUG",
                                                         "INFORMATION",
                                                         "WARNING",
                                                         "ERROR",
                                                         "FATAL"};

inline constexpr std::array<const char*, 8> logTypes =
    {"None", "Core", "Rendering", "Audio", "Input", "Editor", "Scripting", "AssetLoading"};

class Log {
 public:
  LogLevel level;
  LogType type;
  std::string title;
  std::string message;
  std::chrono::system_clock::time_point timestamp;

  Log(LogLevel level, LogType type, std::string message);

  [[nodiscard]] std::string toString() const;

  static std::string LogLevelToString(LogLevel level);
  static std::string LogTypeToString(LogType type);
};

}  // namespace SpaceEngine
