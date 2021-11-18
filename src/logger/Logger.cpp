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

    /**
     * Set level here, and update SPDLOG_ACTIVE_LEVEL in logger/Logger.h
     */
    spdlog::set_level(spdlog::level::trace);
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log setup failed" << ex.what() << std::endl;
  }
}
