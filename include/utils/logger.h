#ifndef LOGGER_H
#define LOGGER_H

// #define INFO 0
// #define DEBUG 1
// #define WARNING 2
// #define ERROR 3
// #define FATAL 4

#define DISABLE_HANDLER(tag) \
({ \
    int out = 0; \
    if (tag == 0) { out = 1; } \
    if (tag == 1) { out = 1; } \
    if (tag == 2) { out = 1; } \
    if (tag == 3) { out = 1; } \
    if (tag == 4) { out = 1; } \
    out; \
})

#define CONVERT_INT_TO_NAME(name_int) \
({ \
    char* name; \
    if (name_int == 0) { name = "INFO"; } \
    else if (name_int == 1) { name = "DEBUG"; } \
    else if (name_int == 2) { name = "WARNING"; } \
    else if (name_int == 3) { name = "ERROR"; } \
    else if (name_int == 4) { name = "FATAL"; } \
    name; \
})

// #define LOGG(TYPE, FORMAT, ...) printf(FORMAT, CONVERTTONAME(TYPE), __VA_ARGS__)

#define INFO 0, __FILE__, __LINE__
#define DEBUG 1, __FILE__, __LINE__
#define WARNING 2, __FILE__, __LINE__
#define ERROR 3, __FILE__, __LINE__
#define FATAL 4, __FILE__, __LINE__

#define DISABLE_INFO 0
#define DISABLE_DEBUG 0
#define DISABLE_WARNING 0
#define DISABLE_ERROR 0
#define DISABLE_FATAL 0

#define FILENAME "sample.log"
#define TIME_FORMAT "%Y-%m-%d %H:%M:%S"

#define Q(x) #x
#define QUOTE(x) Q(x)

#ifdef LOG_FILENAME
    #undef FILENAME
    #define FILENAME QUOTE(LOG_FILENAME)
#endif

#ifdef LOG_TIME_FORMAT
    #undef TIME_FORMAT
    #define TIME_FORMAT QUOTE(LOG_TIME_FORMAT)
#endif

#ifdef LOG_DISABLE_INFO
    #undef DISABLE_INFO
    #define DISABLE_INFO 1, __FILE__, __LINE__
#endif

#ifdef LOG_DISABLE_DEBUG
    #undef DISABLE_DEBUG
    #define DISABLE_DEBUG 1, __FILE__, __LINE__
#endif

#ifdef LOG_DISABLE_WARNING
    #undef LOSABLE_WARNING
    #define SABLE_WARNING 1, __FILE__, __LINE__
#endif

#ifdef LOG_DISABLE_ERROR
    #undef DISABLE_ERROR
    #define DISABLE_ERROR 1, __FILE__, __LINE__
#endif

#ifdef LOG_DISABLE_FATAL
    #undef DISABLE_FATAL
    #define DISABLE_FATAL 1, __FILE__, __LINE__
#endif

void LOG(unsigned tag, const char* file, unsigned line, const char* message);

#endif