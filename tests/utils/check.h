#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <malloc.h>
#endif
#ifdef __APPLE__
#include <stdlib.h>
#include <malloc/malloc.h>
#endif

#define FG_RED "\x1b[31m"
#define FG_GREEN "\x1b[32m"
#define FG_LGRAY "\x1b[37m"
#define RESET_ALL "\x1b[0m"

#define title(s) { \
    char buffer[256]; \
    snprintf(buffer, sizeof(buffer), "%s%s", FG_LGRAY, s); \
    write(1, buffer, strlen(buffer)); \
}

extern int iTest;

void check(int success);
void mcheck(void *p, size_t required_size);

#endif
