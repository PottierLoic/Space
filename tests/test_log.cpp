#include "log/log.hpp"
#include "test.hpp"

using namespace SpaceEngine;

int testLog() {
  // Create a log entry
  const Log log(LogLevel::INFORMATION, LogType::Core, "This is a test log message");

  // Test log level
  custom_assert(log.level == LogLevel::INFORMATION, "Log level incorrect");

  // Test log type
  custom_assert(log.type == LogType::Core, "Log type incorrect");

  // Test log message
  custom_assert(log.message == "This is a test log message", "Log message incorrect");

  // Test log timestamp
  const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  const std::chrono::system_clock::time_point minTimestamp = now - std::chrono::seconds(1);
  const std::chrono::system_clock::time_point maxTimestamp = now + std::chrono::seconds(1);
  custom_assert(log.timestamp >= minTimestamp && log.timestamp <= maxTimestamp,
                "Log timestamp incorrect");

  // Test LogLevelToString() method
  const std::string logLevelString = Log::LogLevelToString(LogLevel::WARNING);
  const std::string expectedLogLevelString = "WARNING";
  custom_assert(logLevelString == expectedLogLevelString, "LogLevelToString() method incorrect");

  // Test LogTypeToString() method
  const std::string logTypeString = Log::LogTypeToString(LogType::Rendering);
  const std::string expectedLogTypeString = "Rendering";
  custom_assert(logTypeString == expectedLogTypeString, "LogTypeToString() method incorrect");

  return 0;
}