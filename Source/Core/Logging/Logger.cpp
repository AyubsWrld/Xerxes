#include "Core/Logging/Logger.hpp"
#include <stdarg.h>
#include <stdio.h>
#include <utility>

static const char* LogLevelPrefixes[] =
{
    "\033[1;31m[FATAL]\033[0m", 
    "\033[31m[Error]\033[0m",  
    "\033[33m[Warn]\033[0m",    
    "\033[32m[Info]\033[0m",    
    "\033[36m[Debug]\033[0m",   
    "\033[90m[Trace]\033[0m",   
};

void PrintLogMessage([[maybe_unused]] LogLevel level, [[maybe_unused]] const char* format, ...)
{
    char buffer[256];
    va_list argptr;
    va_start(argptr, format);
    sprintf(buffer,"%s: %s\n", LogLevelPrefixes[std::to_underlying(level)], format);
    vprintf(buffer,argptr);
    va_end(argptr);
}

namespace Core::Logger
{
    Logger::~Logger() {}

    Logger::Logger() {}

    bool Logger::InitializeLogger() { return {}; }

    void Logger::ShutdownLogger() {}
}
