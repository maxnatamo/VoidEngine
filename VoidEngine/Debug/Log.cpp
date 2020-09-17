#include <cstring>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Time.hpp>
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
        }

        /* Format: "[HH:MM:SS] " */
        char fmt[12];
        struct tm *time = GetTime();
        snprintf(fmt, 12, "[%02d:%02d:%02d] ", time->tm_hour, time->tm_min, time->tm_sec);

        return std::string(fmt) + lvs + " ";
    }

    Logger::Level Logger::GetLogLevel() {
        return Logger::m_Level;
    }

    f32 Logger::GetFramesPerSecond() {
        return 1.0f / Time::GetDeltaTime();
    }

    u64 Logger::GetMemoryAllocations() {
        return Allocator::m_AllocatedSize;
    }
    
    void Logger::SetLogLevel(Logger::Level level) {
        Logger::m_Level = level;
    }
};
