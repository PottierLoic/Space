#include "log/logger.hpp"
#include "test.hpp"

using namespace SpaceEngine;

int testLogger() {
  // Add log entries
  Logger::log(LogLevel::DEBUG, LogType::Core, "Core subsystem initialized successfully.");
  Logger::log(LogLevel::INFORMATION, LogType::Rendering, "OpenGL context created: Version 4.5");
  Logger::log(LogLevel::WARNING,
              LogType::Audio,
              "Audio file 'background.mp3' not found, using fallback.");
  Logger::log(LogLevel::ERROR, LogType::Scripting, "Undefined variable in playerMovement script.");
  Logger::log(LogLevel::FATAL, LogType::Editor, "Unhandled exception caught: Access violation.");
  Logger::log(LogLevel::DEBUG,
              LogType::AssetLoading,
              "Started loading asset bundle 'environment.pack'.");
  Logger::info("Custom control scheme loaded for gamepad.");
  Logger::log(LogLevel::WARNING,
              LogType::AssetLoading,
              "High-resolution texture 'forest.png' may affect performance.");
  Logger::error("Failed to compile vertex shader 'basic.vert'.");
  Logger::log(LogLevel::DEBUG,
              LogType::Scripting,
              "Player script attached to entity 'PlayerCharacter'.");
  Logger::log(LogLevel::DEBUG,
              LogType::Scripting,
              "Enemy script attached to entity 'EnemyController'.");

  // Check if the log entries are added correctly
  custom_assert(Logger::getLogEntries().size() == 11, "Logger log method failed");

  // Check if the filters retrieve the correct entries with log level filter.
  Logger::filter.setLogLevel(LogLevel::DEBUG, true);
  custom_assert(Logger::getLogEntries().size() == 4, "Logger log level filter method failed");

  // Check if the filters retrieve the correct entries with log level/type
  // filter.
  Logger::filter.setLogType(LogType::Scripting, true);
  custom_assert(Logger::getLogEntries().size() == 2, "Logger log type filter method failed");

  // Check if the filters retrieve the correct entries with log
  // level/type/keyword filter.
  Logger::filter.keyword = "Enemy";
  custom_assert(Logger::getLogEntries().size() == 1, "Logger keyword filter method failed");

  // Clear log entries
  Logger::clearLogEntries();
  custom_assert(Logger::getLogEntries().empty(), "Logger clearLogEntries method failed");

  return 0;
}