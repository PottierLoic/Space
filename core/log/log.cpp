#include "log/log.hpp"

namespace SpaceEngine {

Log::Log(const LogLevel level, const LogType type, std::string message)
    : level(level),
      type(type),
      message(std::move(message)),
      timestamp(std::chrono::system_clock::now()) {}

std::string Log::toString() const {
  std::ostringstream stream;
  auto timeT = std::chrono::system_clock::to_time_t(timestamp);
  std::tm tm{};
#ifdef _WIN32
  localtime_s(&tm, &timeT);
#else
  localtime_r(&timeT, &tm);
#endif
  stream << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";
  stream << "[" << LogLevelToString(level) << "] ";
  stream << "[" << LogTypeToString(type) << "] - ";
  stream << message;
  return stream.str();
}

std::string Log::LogLevelToString(const LogLevel level) {
  return logLevels[static_cast<int>(level)];
}

std::string Log::LogTypeToString(const LogType type) {
  return logTypes[static_cast<int>(type)];
}

}  // namespace SpaceEngine
