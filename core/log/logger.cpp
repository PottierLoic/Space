#include "log/logger.hpp"

namespace SpaceEngine {

std::vector<Log> Logger::logEntries;
LogFilter Logger::filter;

void Logger::log(LogLevel level, LogType type, const std::string& title, const std::string& message) {
  logEntries.push_back(Log(level, type, title, message));
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
