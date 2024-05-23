#include "log/logger.hpp"

namespace SpaceEngine {

std::vector<Log> Logger::logEntries;
LogFilter Logger::filter;

void Logger::log(LogLevel level, LogType type, const std::string& message) {
  logEntries.push_back(Log(level, type, message));
}

void Logger::debug(const std::string& message) {
  logEntries.push_back(Log(LogLevel::DEBUG, LogType::None, message));
}

void Logger::info(const std::string& message) {
  logEntries.push_back(Log(LogLevel::INFORMATION, LogType::None, message));
}

void Logger::warn(const std::string& message) {
  logEntries.push_back(Log(LogLevel::WARNING, LogType::None, message));
}

void Logger::error(const std::string& message) {
  logEntries.push_back(Log(LogLevel::ERROR, LogType::None, message));
}

void Logger::fatal(const std::string& message) {
  logEntries.push_back(Log(LogLevel::FATAL, LogType::None, message));
}

std::vector<Log> Logger::getLogEntries() {
  std::vector<Log> filteredLogs;
  for (const auto& log: logEntries) {
    if (filter.matches(log)) {
      filteredLogs.push_back(log);
    }
  }
  return filteredLogs;
}

void Logger::clearLogEntries() {
  logEntries.clear();
}

}
