#ifndef GNL_H
#define GNL_H
#include "leaks.h"

// Don't do that at home
#define TEST(x) { \
    int status = 0; \
    pid_t test = fork(); \
    if (test == 0) { \
        x \
        showLeaks(); \
        exit(EXIT_SUCCESS); \
    } else { \
        usleep(TIMEOUT_US); \
        if (waitpid(test, &status, WNOHANG) == 0) { \
            kill(test, 9); \
            printf("%sTIMEOUT%s\n", FG_RED, RESET_ALL); \
        } \
    } \
}

void gnl(int fd, const char *expectedReturn);

#endif
