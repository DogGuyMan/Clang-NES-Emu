/**
 * @file log.c
 * @brief Logging implementation.
 */
#include "common/log.h"
#include <stdio.h>
#include <stdarg.h>

static LogLevel g_log_level = LOG_INFO;

static const char *level_strings[] = {
    "ERROR", "WARN", "INFO", "DEBUG", "TRACE"
};

void log_set_level(LogLevel level) {
    g_log_level = level;
}

void log_msg(LogLevel level, const char *fmt, ...) {
    if (level > g_log_level) {
        return;
    }

    fprintf(stderr, "[%s] ", level_strings[level]);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n");
}
