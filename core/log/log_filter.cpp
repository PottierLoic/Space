#include "log/log_filter.hpp"

namespace SpaceEngine {

void LogFilter::setLogLevel(LogLevel level, bool enable) {
  if (enable) {
    levels.insert(level);
  } else {
    levels.erase(level);
  }
}

void LogFilter::setLogType(LogType type, bool enable) {
  if (enable) {
    types.insert(type);
  } else {
    types.erase(type);
  }
}

bool LogFilter::matches(const Log& log) const {
  bool matchesLevel = levels.empty() || levels.find(log.level) != levels.end();
  bool matchesType = types.empty() || types.find(log.type) != types.end();
  bool matchesKeyword = keyword.empty() ||
                        log.toString().find(keyword) != std::string::npos;
  return matchesLevel && matchesType && matchesKeyword;
}

}