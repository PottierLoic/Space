#pragma once

#include <string>
#include <set>
#include <vector>

#include "log/log.hpp"

namespace SpaceEngine {

class LogFilter {
public:
  std::set<LogLevel> levels;
  std::set<LogType> types;
  std::string keyword;

  void setLogLevel(LogLevel level, bool enable);
  void setLogType(LogType type, bool enable);
  bool matches(const Log& log) const;
};

}
