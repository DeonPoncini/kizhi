#include <kizhi/Log.h>

#ifdef ANDROID
#include <android/log.h>
#else
#include <iostream>
#include <cstdlib>
#endif

namespace kizhi
{

Level Log::MIN_LEVEL;

Log::Log(Level level) :
    mLevel(level),
    mOptions(0)
{
    setLevel();
}

Log::Log(Level level, const char* file, int line) :
    mLevel(level),
    mFile(file),
    mLine(line),
    mOptions(FILE_LINE)
{
    setLevel();
}

Log::Log(Level level, std::string tag) :
    mLevel(level),
    mTag(tag),
    mOptions(TAG)
{
    setLevel();
}

Log::Log(Level level, std::string tag, const char* file, int line) :
    mLevel(level),
    mTag(std::move(tag)),
    mFile(file),
    mLine(line),
    mOptions(TAG | FILE_LINE)
{
    setLevel();
}

Log::~Log()
{
#define LOG_SEL(l)                                    \
    if ((mOptions & TAG) && (mOptions & FILE_LINE)) { \
        LOG_TF(l)                                     \
    } else if (mOptions & TAG) {                      \
        LOG_T(l)                                      \
    } else if (mOptions & FILE_LINE) {                \
        LOG_F(l)                                      \
    } else {                                          \
        LOG(l)                                        \
    }


#ifdef ANDROID
#define LOG_TF(l) __android_log_print(l, mTag.c_str(), \
        "%s:%d %s", mFile.c_str(), mLine, mBuffer.str().c_str());
#define LOG_T(l) __android_log_print(l, mTag.c_str(), \
        "%s", mBuffer.str().c_str());
#define LOG_F(l) __android_log_print(l, "", \
        "%s:%d %s", mFile.c_str(), mLine, mBuffer.str().c_str());
#define LOG(l) __android_log_print(l, "", "%s", mBuffer.str().c_str());

    switch (mLevel) {
        case Level::ALL: break;
        case Level::TRACE: LOG_SEL(ANDROID_LOG_VERBOSE); break;
        case Level::DEBUG: LOG_SEL(ANDROID_LOG_DEBUG); break;
        case Level::INFO: LOG_SEL(ANDROID_LOG_INFO); break;
        case Level::WARN: LOG_SEL(ANDROID_LOG_WARN); break;
        case Level::ERROR: LOG_SEL(ANDROID_LOG_ERROR); break;
        case Level::FATAL: LOG_SEL(ANDROID_LOG_FATAL); break;
        case Level::SILENT: break;
    }

#else
    // don't display if below min level
    if (mLevel < MIN_LEVEL) {
        return;
    }

#define LOG_TF(l) std::cout << l << ": " << mFile << ":" << mLine << \
        " [" << mTag << "] " << mBuffer.str() << std::endl;
#define LOG_T(l) std::cout << l << ": [" << mTag << "] " << \
    mBuffer.str() << std::endl;
#define LOG_F(l) std::cout << l << ": " << mFile << ":" << mLine << \
        " " << mBuffer.str() << std::endl;
#define LOG(l) std::cout << l << ": " << mBuffer.str() << std::endl;

    switch (mLevel) {
        case Level::ALL: break;
        case Level::TRACE: LOG_SEL("TRACE"); break;
        case Level::DEBUG: LOG_SEL("DEBUG"); break;
        case Level::INFO: LOG_SEL("INFO"); break;
        case Level::WARN: LOG_SEL("WARN"); break;
        case Level::ERROR: LOG_SEL("ERROR"); break;
        case Level::FATAL: LOG_SEL("FATAL"); break;
        case Level::SILENT: break;
    }

#endif

}

void Log::setLevel()
{
#ifndef ANDROID
    // check the environment to set a default log level
    auto l = getenv("KIZHI_MIN_LEVEL");
    if (l == nullptr) {
        MIN_LEVEL = Level::WARN;
    } else {
        std::string level(l);
        if (level == "ALL") {
            MIN_LEVEL = Level::ALL;
        } else if (level == "TRACE") {
            MIN_LEVEL = Level::TRACE;
        } else if (level == "DEBUG") {
            MIN_LEVEL = Level::DEBUG;
        } else if (level == "INFO") {
            MIN_LEVEL = Level::INFO;
        } else if (level == "WARN") {
            MIN_LEVEL = Level::WARN;
        } else if (level == "ERROR") {
            MIN_LEVEL = Level::ERROR;
        } else if (level == "FATAL") {
            MIN_LEVEL = Level::FATAL;
        } else if (level == "SILENT") {
            MIN_LEVEL = Level::SILENT;
        } else {
            MIN_LEVEL = Level::WARN;
        }
    }
#endif
}

}
