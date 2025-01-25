#include "utils/logger.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include "stdbool.h"

pthread_mutex_t logger_mutex = PTHREAD_MUTEX_INITIALIZER;

void LOG(unsigned tag, const char* file, unsigned line, const char* message) {
    // Disable log based on log-type.
    DISABLE_HANDLER(tag);

    // Lock log file.
    pthread_mutex_lock(&logger_mutex);

    FILE *fp;
    fp = fopen(FILENAME, "a");

    time_t now;
    time(&now);
    char *t = ctime(&now);

    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    // Get and format time.
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, TIME_FORMAT, tm_info);
    if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
    // std::cout << "MESSAGE: " << message << std::endl;
    // Write to file.
    printf("%s [%s]: %s:%d %s\n", buffer, CONVERT_INT_TO_NAME(tag), file, line, message);
    // fclose(fp);

    // Unlock log file.
    pthread_mutex_unlock(&logger_mutex);
}