#include <kizhi/Log.h>

#ifdef ANDROID
#include <android/log.h>
#else
#include <iostream>
#endif

namespace kizhi
{

Log::Log(Level level, std::string tag, const char* file, int line) :
    mLevel(level), mTag(std::move(tag)), mFile(file), mLine(line)
{
}

Log::~Log()
{
#ifdef ANDROID
#define LOG(l) __android_log_print(ANDROID_LOG_##l, mTag.c_str(), \
        "%s:%d %s", mFile.c_str(), mLine, mBuffer.str().c_str())

    switch (mLevel) {
        case Level::TRACE: LOG(VERBOSE); break;
        case Level::DEBUG: LOG(DEBUG); break;
        case Level::INFO: LOG(INFO); break;
        case Level::WARNING: LOG(WARN); break;
        case Level::ERROR: LOG(ERROR); break;
        case Level::FATAL: LOG(FATAL); break;
    }

#else
#define LOG(l) l << ": " << mFile << ":" << mLine << \
        " [" << mTag << "] " << mBuffer.str() << std::endl;
#define LOG_OUT(l) std::cout << LOG(l)
#define LOG_ERR(l) std::cerr << LOG(l)

    switch (mLevel) {
        case Level::TRACE: LOG_OUT("TRACE"); break;
        case Level::DEBUG: LOG_OUT("DEBUG"); break;
        case Level::INFO: LOG_OUT("INFO"); break;
        case Level::WARNING: LOG_OUT("WARNING"); break;
        case Level::ERROR: LOG_ERR("ERROR"); break;
        case Level::FATAL: LOG_ERR("FATAL"); break;
    }

#endif

}

}
