#pragma once

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace SpaceEngine {

enum LogLevel {
  DEBUG,
  INFORMATION,
  WARNING,
  ERROR,
  FATAL
};

enum LogType {
  Core,
  Rendering,
  Audio,
  Input,
  Editor,
  Scripting,
  AssetLoading,
};

class Log {
public:
  LogLevel level;
  LogType type;
  std::string title;
  std::string message;
  std::chrono::system_clock::time_point timestamp;

  Log(LogLevel level, LogType type, const std::string& title, const std::string& message);
  std::string toString();

  static std::string LogLevelToString(LogLevel level);
  static std::string LogTypeToString(LogType type);
};

}