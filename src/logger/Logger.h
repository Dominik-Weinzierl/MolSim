#pragma once

/**
 * Sets global log level during compile time.
 */
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/**
 * Wrapper for spdlog to define the global log level during compile time.
 */
class Logger {
 public:
  /**
   * Setup the logger.
   */
  static void setupLogger();
};