#include "test.hpp"
#include "log/log.hpp"

using namespace SpaceEngine;

int testLog() {
  // Create a log entry
  Log log(LogLevel::INFORMATION, LogType::Core, "Test Log", "This is a test log message");

  // Test log level
  custom_assert(log.level == LogLevel::INFORMATION, "Log level incorrect");

  // Test log type
  custom_assert(log.type == LogType::Core, "Log type incorrect");

  // Test log title
  custom_assert(log.title == "Test Log", "Log title incorrect");

  // Test log message
  custom_assert(log.message == "This is a test log message", "Log message incorrect");

  // Test log timestamp
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::chrono::system_clock::time_point minTimestamp = now - std::chrono::seconds(1);
  std::chrono::system_clock::time_point maxTimestamp = now + std::chrono::seconds(1);
  custom_assert(log.timestamp >= minTimestamp && log.timestamp <= maxTimestamp, "Log timestamp incorrect");

  // Test LogLevelToString() method
  std::string logLevelString = Log::LogLevelToString(LogLevel::WARNING);
  std::string expectedLogLevelString = "WARNING";
  custom_assert(logLevelString == expectedLogLevelString, "LogLevelToString() method incorrect");

  // Test LogTypeToString() method
  std::string logTypeString = Log::LogTypeToString(LogType::Rendering);
  std::string expectedLogTypeString = "Rendering";
  custom_assert(logTypeString == expectedLogTypeString, "LogTypeToString() method incorrect");

  return 0;
}