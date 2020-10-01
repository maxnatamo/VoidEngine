#include <execinfo.h>
#include <cstring>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    Logger::Level Logger::m_Level = Logger::Level::Warning;

    struct tm *Logger::GetTime() {
        time_t now = time(0);
        return gmtime(&now);
    }

    std::string Logger::GetLogPrefix(Level lvl) {
        std::string lvs;
        switch(lvl) {
            case Level::Debug:      lvs = "[DEBUG]";    break;
            case Level::Info:       lvs = "[INFO]";     break;
            case Level::Warning:    lvs = "[WARNING]";  break;
            case Level::Error:      lvs = "[ERROR]";    break;
            case Level::Fatal:      lvs = "[FATAL]";    break;
            case Level::Assert:     lvs = "[ASSERT]";   break;
        }

        /* Format: "[HH:MM:SS] " */
        char fmt[12];
        struct tm *time = GetTime();
        snprintf(fmt, 12, "[%02d:%02d:%02d] ", time->tm_hour, time->tm_min, time->tm_sec);

        return std::string(fmt) + lvs + " ";
    }

    string Logger::GetBacktrace() {
        string output = "";
        char buffer[1024];
        const u32 backtraceSize = 64;
        void *callstack[backtraceSize];

        int frameCount = backtrace(callstack, backtraceSize);
        char **symbols = backtrace_symbols(callstack, frameCount);

        for(u32 i = 0; i < frameCount; i++) {
            snprintf(buffer, LEN(buffer), "  %-5d %p  %s\n", i, callstack[i], symbols[i]);
            output += buffer;
        }

        free(symbols);
        return output;
    }
};
