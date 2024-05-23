#pragma once

#include <string>
#include <vector>

#include "log/log.hpp"
#include "log/log_filter.hpp"

namespace SpaceEngine {

class Logger {
public:
  static LogFilter filter;

  /**
   * @brief Logs a message with the specified log level, type, title, and message.
   *
   * @param level The log level of the message.
   * @param type The type of the log entry.
   * @param message The message of the log entry.
   */
  static void log(LogLevel level, LogType type, const std::string& message);
  static void debug(const std::string& message);
  static void info(const std::string& message);
  static void warn(const std::string& message);
  static void error(const std::string& message);
  static void fatal(const std::string& message);

  static std::vector<Log> getLogEntries();

  /**
   * @brief Clears all log entries.
   */
  static void clearLogEntries();

private:
  static std::vector<Log> logEntries;
};

}
