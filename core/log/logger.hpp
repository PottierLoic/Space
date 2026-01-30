#pragma once

#include <string>
#include <vector>

#include "log/log.hpp"
#include "log/log_filter.hpp"

namespace SpaceEngine {

class Logger {
 public:
  static LogFilter filter;

  static void log(LogLevel level, LogType type, const std::string& message);
  static void debug(const std::string& message);
  static void info(const std::string& message);
  static void warn(const std::string& message);
  static void error(const std::string& message);
  static void fatal(const std::string& message);

  static std::vector<Log> getLogEntries();

  static void clearLogEntries();

 private:
  static std::vector<Log> logEntries;
};

}  // namespace SpaceEngine
