#include <kizhi/Log.h>

#ifdef ANDROID
#include <android/log.h>
#else
#include <iostream>
#endif

namespace kizhi
{

Log::Log(Level level) :
    mLevel(level),
    mUseTag(false),
    mUseFileLine(false)
{
}

Log::Log(Level level, const char* file, int line) :
    mLevel(level),
    mFile(file),
    mLine(line),
    mUseTag(false),
    mUseFileLine(true)
{
}

Log::Log(Level level, std::string tag) :
    mLevel(level),
    mTag(tag),
    mUseTag(true),
    mUseFileLine(false)
{
}

Log::Log(Level level, std::string tag, const char* file, int line) :
    mLevel(level),
    mTag(std::move(tag)),
    mFile(file),
    mLine(line),
    mUseTag(true),
    mUseFileLine(true)
{
}

Log::~Log()
{
#define LOG_SEL(l)                 \
    if (mUseTag && mUseFileLine) { \
        LOG_TF(l)                  \
    } else if (mUseTag) {          \
        LOG_T(l)                   \
    } else if (mUseFileLine) {     \
        LOG_F(l)                   \
    } else {                       \
        LOG(l)                     \
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
        case Level::TRACE: LOG_SEL(ANDROID_LOG_VERBOSE); break;
        case Level::DEBUG: LOG_SEL(ANDROID_LOG_DEBUG); break;
        case Level::INFO: LOG_SEL(ANDROID_LOG_INFO); break;
        case Level::WARN: LOG_SEL(ANDROID_LOG_WARN); break;
        case Level::ERROR: LOG_SEL(ANDROID_LOG_ERROR); break;
        case Level::FATAL: LOG_SEL(ANDROID_LOG_FATAL); break;
    }

#else
#define LOG_TF(l) std::cout << l << ": " << mFile << ":" << mLine << \
        " [" << mTag << "] " << mBuffer.str() << std::endl;
#define LOG_T(l) std::cout << l << ": [" << mTag << "] " << \
    mBuffer.str() << std::endl;
#define LOG_F(l) std::cout << l << ": " << mFile << ":" << mLine << \
        " " << mBuffer.str() << std::endl;
#define LOG(l) std::cout << l << ": " << mBuffer.str() << std::endl;

    switch (mLevel) {
        case Level::TRACE: LOG_SEL("TRACE"); break;
        case Level::DEBUG: LOG_SEL("DEBUG"); break;
        case Level::INFO: LOG_SEL("INFO"); break;
        case Level::WARN: LOG_SEL("WARN"); break;
        case Level::ERROR: LOG_SEL("ERROR"); break;
        case Level::FATAL: LOG_SEL("FATAL"); break;
    }

#endif

}

}
