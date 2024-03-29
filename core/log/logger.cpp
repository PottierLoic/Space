#include "log/logger.hpp"

namespace SpaceEngine {

std::vector<Log> Logger::logEntries;
LogLevel Logger::globalLogLevel = LogLevel::INFORMATION;

void Logger::setGlobalLogLevel(LogLevel level) {
  globalLogLevel = level;
}

void Logger::log(LogLevel level, LogType type, const std::string& title, const std::string& message) {
  if (level >= globalLogLevel) {
    logEntries.push_back(Log(level, type, title, message));
  }
}

void Logger::clearLogEntries() {
  logEntries.clear();
}

}