#ifndef DEVNULL_H
#define DEVNULL_H

#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>

// No-op log output destination
class DevNull {
  public:
    template <class T>
    DevNull& operator<<(T t) { return *this; }
};

/**
 * Application log
 *
 * Example: 
 *
 *   LOG(error) << "Bad pointer";
 *
 * Levels: trace info warning error fatal
*/
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(logger, boost::log::sources::severity_logger<\
    boost::log::trivial::severity_level>)
#define LOG(level) BOOST_LOG_SEV(logger::get(),boost::log::trivial::level)
#endif

/**
 * Debug log
 *
 * Enabled in .cc files with #define DEBUG true at the top
 * (they must include debug.h)
 *
 * Example: 
 *
 *   DBG << "InfernoCop and 'a -> 'a not unifiable.";
 *
 */
#if DEBUG
#define DBG BOOST_LOG_TRIVIAL(debug)
#else
#define DBG DevNull() 
#endif
