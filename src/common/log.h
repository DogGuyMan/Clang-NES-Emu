/**
 * @file log.h
 * @brief Simple logging interface with severity levels.
 */
#ifndef NES_LOG_H
#define NES_LOG_H

typedef enum {
    LOG_ERROR = 0,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE
} LogLevel;

void log_set_level(LogLevel level);

#ifdef __GNUC__
__attribute__((format(printf, 2, 3)))
#endif
void log_msg(LogLevel level, const char *fmt, ...);

#define LOG_ERROR(...) log_msg(LOG_ERROR, __VA_ARGS__)
#define LOG_WARN(...)  log_msg(LOG_WARN,  __VA_ARGS__)
#define LOG_INFO(...)  log_msg(LOG_INFO,  __VA_ARGS__)
#define LOG_DEBUG(...) log_msg(LOG_DEBUG, __VA_ARGS__)
#define LOG_TRACE(...) log_msg(LOG_TRACE, __VA_ARGS__)

#endif /* NES_LOG_H */
