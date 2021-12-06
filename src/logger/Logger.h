#pragma once

/**
 * Sets global log level during compile time.
 */
#ifdef USE_SPD_LOG_OFF
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#endif
#ifdef USE_SPD_LOG_TRACE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#ifdef USE_SPD_LOG_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif
#ifdef USE_SPD_LOG_INFO
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif
#ifdef USE_SPD_LOG_WARN
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_WARN
#endif
#ifdef USE_SPD_LOG_ERROR
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_ERROR
#endif
#ifdef USE_SPD_LOG_CRITICAL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_CRITICAL
#endif

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