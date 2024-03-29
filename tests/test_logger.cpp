#include "test.hpp"
#include "log/logger.hpp"

using namespace SpaceEngine;

int testLogger() {
  // Add log entries
  Logger::log(LogLevel::DEBUG, LogType::Core, "Initialization", "Core subsystem initialized successfully.");
  Logger::log(LogLevel::INFORMATION, LogType::Rendering, "Graphics", "OpenGL context created: Version 4.5");
  Logger::log(LogLevel::WARNING, LogType::Audio, "Audio Warning", "Audio file 'background.mp3' not found, using fallback.");
  Logger::log(LogLevel::ERROR, LogType::Scripting, "Script Error", "Undefined variable in playerMovement script.");
  Logger::log(LogLevel::FATAL, LogType::Editor, "Crash Report", "Unhandled exception caught: Access violation.");
  Logger::log(LogLevel::DEBUG, LogType::AssetLoading, "Asset Load", "Started loading asset bundle 'environment.pack'.");
  Logger::log(LogLevel::INFORMATION, LogType::Input, "Input Mapping", "Custom control scheme loaded for gamepad.");
  Logger::log(LogLevel::WARNING, LogType::AssetLoading, "Texture Load", "High-resolution texture 'forest.png' may affect performance.");
  Logger::log(LogLevel::ERROR, LogType::Rendering, "Shader Compilation", "Failed to compile vertex shader 'basic.vert'.");
  Logger::log(LogLevel::DEBUG, LogType::Scripting, "Script Debug", "Player script attached to entity 'PlayerCharacter'.");
  Logger::log(LogLevel::DEBUG, LogType::Scripting, "Script Debug", "Enemy script attached to entity 'EnemyController'.");

  // Check if the log entries are added correctly
  custom_assert(Logger::getLogEntries().size() == 11, "Logger log method failed");

  // Check if the filters retrieve the correct entries with log level filter.
  Logger::filter.setLogLevel(LogLevel::DEBUG, true);
  custom_assert(Logger::getLogEntries().size() == 4, "Logger log level filter method failed");

  // Check if the filters retrieve the correct entries with log level/type filter.
  Logger::filter.setLogType(LogType::Scripting, true);
  custom_assert(Logger::getLogEntries().size() == 2, "Logger log type filter method failed");
  
  // Check if the filters retrieve the correct entries with log level/type/keyword filter.
  Logger::filter.keyword = "Enemy";
  custom_assert(Logger::getLogEntries().size() == 1, "Logger keyword filter method failed");

  // Clear log entries
  Logger::clearLogEntries();
  custom_assert(Logger::getLogEntries().empty(), "Logger clearLogEntries method failed");

  return 0;
}