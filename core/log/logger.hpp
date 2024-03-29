#pragma once

#include <string>
#include <vector>

#include "log/log.hpp"

namespace SpaceEngine {

class Logger {
public:
  static std::vector<Log> logEntries;

  static void setGlobalLogLevel(LogLevel level);
  static void log(LogLevel level, LogType type, const std::string& title, const std::string& message);
  static void clearLogEntries();

private:
  static LogLevel globalLogLevel;
};

}