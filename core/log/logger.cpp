#include "log/logger.hpp"

namespace SpaceEngine {

std::vector<Log> Logger::logEntries;
LogFilter Logger::filter;

void Logger::log(const LogLevel level, const LogType type, const std::string& message) {
  logEntries.emplace_back(level, type, message);
}

void Logger::debug(const std::string& message) {
  logEntries.emplace_back(LogLevel::DEBUG, LogType::None, message);
}

void Logger::info(const std::string& message) {
  logEntries.emplace_back(LogLevel::INFORMATION, LogType::None, message);
}

void Logger::warn(const std::string& message) {
  logEntries.emplace_back(LogLevel::WARNING, LogType::None, message);
}

void Logger::error(const std::string& message) {
  logEntries.emplace_back(LogLevel::ERROR, LogType::None, message);
}

void Logger::fatal(const std::string& message) {
  logEntries.emplace_back(LogLevel::FATAL, LogType::None, message);
}

std::vector<Log> Logger::getLogEntries() {
  std::vector<Log> filteredLogs;
  for (const auto& log : logEntries) {
    if (filter.matches(log)) {
      filteredLogs.push_back(log);
    }
  }
  return filteredLogs;
}

void Logger::clearLogEntries() {
  logEntries.clear();
}

}  // namespace SpaceEngine
