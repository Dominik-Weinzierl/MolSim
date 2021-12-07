#include <iomanip>
#include <iostream>

#include "Logger.h"

void Logger::setupLogger() {
  try {
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto stderrSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

    std::stringstream ss;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    ss << "logs/" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%X");
    std::string logName{ss.str()};

    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logName, true);

    stdoutSink->set_level(spdlog::level::info);
    stderrSink->set_level(spdlog::level::warn);
    fileSink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sinks = {stdoutSink, stderrSink, fileSink};
    spdlog::logger logger("logger", sinks.begin(), sinks.end());
    spdlog::set_default_logger(std::make_shared<spdlog::logger>(logger));

#ifdef USE_SPD_LOG_OFF
    spdlog::set_level(spdlog::level::off);
#endif
#ifdef USE_SPD_LOG_TRACE
    spdlog::set_level(spdlog::level::trace);
#endif
#ifdef USE_SPD_LOG_DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
#ifdef USE_SPD_LOG_INFO
    spdlog::set_level(spdlog::level::info);
#endif
#ifdef USE_SPD_LOG_WARN
    spdlog::set_level(spdlog::level::warn);
#endif
#ifdef USE_SPD_LOG_ERROR
    spdlog::set_level(spdlog::level::error);
#endif
#ifdef USE_SPD_LOG_CRITICAL
    spdlog::set_level(spdlog::level::critical);
#endif
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log setup failed" << ex.what() << std::endl;
  }
}
