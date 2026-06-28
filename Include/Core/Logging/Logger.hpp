#pragma once

#include <format>
#include <utility>

#define XERXES_LOG_WARN_ENABLED 1
#define XERXES_LOG_INFO_ENABLED 1
#define XERXES_LOG_DEBUG_ENABLED 1
#define XERXES_LOG_TRACE_ENABLED 1

#ifdef XERXES_RELEASE
#undef XERXES_LOG_TRACE_ENABLED
#undef XERXES_LOG_DEBUG_ENABLED
#endif

#ifdef XERXES_COMPILED_LIB
#undef XERXES_HEADER_ONLY
#if defined(XERXES_SHARED_LIB)
#if defined(_WIN32)
#ifdef spdlog_EXPORTS
#define XERXES_API __declspec(dllexport)
#else  // !spdlog_EXPORTS
#define XERXES_API __declspec(dllimport)
#endif
#else  // !defined(_WIN32)
#define XERXES_API __attribute__((visibility("default")))
#endif
#else  // !defined(XERXES_SHARED_LIB)
#define XERXES_API
#endif
#define XERXES_INLINE
#else  // !defined(XERXES_COMPILED_LIB)
#define XERXES_API
#define XERXES_HEADER_ONLY
#define XERXES_INLINE inline
#endif  // #ifdef XERXES_COMPILED_LIB

#include <iostream> // FIXME:

#define XERXES_LEVEL_TRACE 0
#define XERXES_LEVEL_DEBUG 1
#define XERXES_LEVEL_INFO 2
#define XERXES_LEVEL_WARN 3
#define XERXES_LEVEL_ERROR 4
#define XERXES_LEVEL_FATAL 5
#define XERXES_LEVEL_OFF 6

enum class LogLevel : int
{
    Trace = XERXES_LEVEL_TRACE,
    Debug = XERXES_LEVEL_DEBUG,
    Info = XERXES_LEVEL_INFO,
    Warn = XERXES_LEVEL_WARN,
    Error = XERXES_LEVEL_ERROR,
    Fatal = XERXES_LEVEL_FATAL,
    Off = XERXES_LEVEL_OFF,
    n_levels
};


template <typename... Args>
#if __cpp_lib_format >= 202207L
using format_string_t = std::format_string<Args...>;
#else
using format_string_t = std::string_view;
#endif

// template <typename... Args>
// void Log([[maybe_unused]] LogLevel level, [[maybe_unused]] const char* format, Args&&... args);

template <typename... Args>
inline std::string Log(LogLevel level, std::format_string<Args...> format, Args... args)
{
    return std::format(format, std::forward<Args...>(args...));
}

template <typename... Args>
void Debug([[maybe_unused]] std::format_string<Args...> format, Args... args)
{
    std::cout << Log(LogLevel::Debug, format, std::forward<Args...>(args...));
}

#define XXFATAL(format, ...)                                                  \
    Log(LogLevel::Fatal, format, __VA_ARGS__);
#define XXERROR(format, ...)                                                  \
    Log(LogLevel::Error, format, ##__VA_ARGS__);
#define XXWARN(format, ...)                                                   \
    Log(LogLevel::Warn, format, ##__VA_ARGS__);
#define XXINFO(format, ...)                                                   \
    Log(LogLevel::Info, format, ##__VA_ARGS__);
#define XXDEBUG(format, ...)                                                  \
    Log(LogLevel::Debug, format, ##__VA_ARGS__);
#define XXTRACE(format, ...)                                                  \
    Log(LogLevel::Trace, format, ##__VA_ARGS__);

namespace Core::Logger
{
    struct Logger
    {

        ~Logger();
        Logger();

        [[nodiscard]]
        bool InitializeLogger();

        void ShutdownLogger();
    };
}
