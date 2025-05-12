#pragma once

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <array>
#include <utility>

namespace SpaceEngine {

enum LogLevel {
  DEBUG,
  INFORMATION,
  WARNING,
  ERROR,
  FATAL
};

enum LogType {
  None,
  Core,
  Rendering,
  Audio,
  Input,
  Editor,
  Scripting,
  AssetLoading
};

inline constexpr std::array<const char*, 5> logLevels = {
  "DEBUG", "INFORMATION", "WARNING", "ERROR", "FATAL"
};

inline constexpr std::array<const char*, 8> logTypes = {
  "None", "Core", "Rendering", "Audio", "Input", "Editor", "Scripting", "AssetLoading"
};

/**
 * @brief Class representing a log entry.
 */
class Log {
public:
  LogLevel level;
  LogType type;
  std::string title;
  std::string message;
  std::chrono::system_clock::time_point timestamp;

  /**
   * @brief Constructor for Log class.
   * @param level The log level.
   * @param type The log type.
   * @param message The log message.
   */
  Log(LogLevel level, LogType type, std::string  message);

  /**
   * @brief Converts the log entry to a string representation.
   * @return The log entry as a string.
   */
  [[nodiscard]] std::string toString() const;

  /**
   * @brief Converts a log level to its string representation.
   * @param level The log level.
   * @return The string representation of the log level.
   */
  static std::string LogLevelToString(LogLevel level);

  /**
   * @brief Converts a log type to its string representation.
   * @param type The log type.
   * @return The string representation of the log type.
   */
  static std::string LogTypeToString(LogType type);
};

}
