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
    WARNING,
    ERROR,
    FATAL,
};

class Log
{
public:
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

#define KIZHI_TRACE(tag) kizhi::Log(kizhi::Level::TRACE, tag, __FILE__, __LINE__)
#define KIZHI_DEBUG(tag) kizhi::Log(kizhi::Level::DEBUG, tag, __FILE__, __LINE__)
#define KIZHI_INFO(tag) kizhi::Log(kizhi::Level::INFO, tag, __FILE__, __LINE__)
#define KIZHI_WARNING(tag) kizhi::Log(kizhi::Level::WARNING, tag, __FILE__, __LINE__)
#define KIZHI_ERROR(tag) kizhi::Log(kizhi::Level::ERROR, tag, __FILE__, __LINE__)
#define KIZHI_FATAL(tag) kizhi::Log(kizhi::Level::FATAL, tag, __FILE__, __LINE__)

#endif
