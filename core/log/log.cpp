#include "log/log.hpp"

namespace SpaceEngine {

Log::Log(LogLevel level, LogType type, const std::string& message)
  : level(level), type(type), message(message), timestamp(std::chrono::system_clock::now()) {}

std::string Log::toString() const {
  std::ostringstream stream;
  auto timeT = std::chrono::system_clock::to_time_t(timestamp);
  auto tm = *std::localtime(&timeT);
  stream << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";
  stream << "[" << LogLevelToString(level) << "] ";
  stream << "[" << LogTypeToString(type) << "] - ";
  stream << message;
  return stream.str();
}

std::string Log::LogLevelToString(LogLevel level) {
  switch(level) {
    case DEBUG: return "DEBUG";
    case INFORMATION: return "INFORMATION";
    case WARNING: return "WARNING";
    case ERROR: return "ERROR";
    case FATAL: return "FATAL";
    default: return "UNKNOWN";
  }
}

std::string Log::LogTypeToString(LogType type) {
  switch(type) {
    case Core: return "Core";
    case Rendering: return "Rendering";
    case Audio: return "Audio";
    case Input: return "Input";
    case Editor: return "Editor";
    case Scripting: return "Scripting";
    case AssetLoading: return "AssetLoading";
    default: return "Unknown";
  }
}

}
