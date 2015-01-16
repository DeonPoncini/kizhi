#ifndef KIZHI_LOG_H
#define KIZHI_LOG_H

#include <string>
#include <sstream>

namespace kizhi
{

enum class Level
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
};

class Log
{
public:
    Log(Level level);
    Log(Level level, const char* file, int line);
    Log(Level level, std::string tag);
    Log(Level level, std::string tag, const char* file, int line);
    ~Log();

    template <typename T>
    inline Log& operator<<(T t) { this->mBuffer << t; return *this; }

private:
    Level mLevel;
    std::string mTag;
    std::string mFile;
    int mLine;
    std::stringstream mBuffer;

    // configuration flags
    bool mUseTag;
    bool mUseFileLine;
};

template <>
inline Log& Log::operator<<(bool t)
{
    this->mBuffer << (t ? "true" : "false");
    return *this;
}

template <>
inline Log& Log::operator<<(std::ostream& (*pf)(std::ostream&))
{
    (*pf)(this->mBuffer);
    return *this;
}

}

#define KIZHI_TRACE_TF(tag) kizhi::Log(kizhi::Level::TRACE, tag, __FILE__, __LINE__)
#define KIZHI_DEBUG_TF(tag) kizhi::Log(kizhi::Level::DEBUG, tag, __FILE__, __LINE__)
#define KIZHI_INFO_TF(tag) kizhi::Log(kizhi::Level::INFO, tag, __FILE__, __LINE__)
#define KIZHI_WARN_TF(tag) kizhi::Log(kizhi::Level::WARN, tag, __FILE__, __LINE__)
#define KIZHI_ERROR_TF(tag) kizhi::Log(kizhi::Level::ERROR, tag, __FILE__, __LINE__)
#define KIZHI_FATAL_TF(tag) kizhi::Log(kizhi::Level::FATAL, tag, __FILE__, __LINE__)

#define KIZHI_TRACE_T(tag) kizhi::Log(kizhi::Level::TRACE, tag)
#define KIZHI_DEBUG_T(tag) kizhi::Log(kizhi::Level::DEBUG, tag)
#define KIZHI_INFO_T(tag) kizhi::Log(kizhi::Level::INFO, tag)
#define KIZHI_WARN_T(tag) kizhi::Log(kizhi::Level::WARN, tag)
#define KIZHI_ERROR_T(tag) kizhi::Log(kizhi::Level::ERROR, tag)
#define KIZHI_FATAL_T(tag) kizhi::Log(kizhi::Level::FATAL, tag)

#define KIZHI_TRACE_F kizhi::Log(kizhi::Level::TRACE, __FILE__, __LINE__)
#define KIZHI_DEBUG_F kizhi::Log(kizhi::Level::DEBUG, __FILE__, __LINE__)
#define KIZHI_INFO_F kizhi::Log(kizhi::Level::INFO, __FILE__, __LINE__)
#define KIZHI_WARN_F kizhi::Log(kizhi::Level::WARN, __FILE__, __LINE__)
#define KIZHI_ERROR_F kizhi::Log(kizhi::Level::ERROR, __FILE__, __LINE__)
#define KIZHI_FATAL_F kizhi::Log(kizhi::Level::FATAL, __FILE__, __LINE__)

#define KIZHI_TRACE kizhi::Log(kizhi::Level::TRACE)
#define KIZHI_DEBUG kizhi::Log(kizhi::Level::DEBUG)
#define KIZHI_INFO kizhi::Log(kizhi::Level::INFO)
#define KIZHI_WARN kizhi::Log(kizhi::Level::WARN)
#define KIZHI_ERROR kizhi::Log(kizhi::Level::ERROR)
#define KIZHI_FATAL kizhi::Log(kizhi::Level::FATAL)

#endif
