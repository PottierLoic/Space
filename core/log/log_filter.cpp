#include "log/log_filter.hpp"

namespace SpaceEngine {

void LogFilter::setLogLevel(const LogLevel level, const bool enable) {
  if (enable) {
    levels.insert(level);
  } else {
    levels.erase(level);
  }
}

void LogFilter::setLogType(const LogType type, const bool enable) {
  if (enable) {
    types.insert(type);
  } else {
    types.erase(type);
  }
}

bool LogFilter::matches(const Log& log) const {
  const bool matchesLevel = levels.empty() || levels.find(log.level) != levels.end();
  const bool matchesType = types.empty() || types.find(log.type) != types.end();
  const bool matchesKeyword = keyword.empty() || log.toString().find(keyword) != std::string::npos;
  return matchesLevel && matchesType && matchesKeyword;
}

}