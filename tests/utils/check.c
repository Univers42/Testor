#include "check.h"
#include <unistd.h>

extern int iTest;

void check(int success)
{
    char buffer[256];

    if (success)
        snprintf(buffer, sizeof(buffer), "%s%d.OK %s", FG_GREEN, iTest, RESET_ALL);
    else
        snprintf(buffer, sizeof(buffer), "%s%d.KO %s", FG_RED, iTest, RESET_ALL);

    write(1, buffer, strlen(buffer));
}

void mcheck(void *p, size_t required_size)
{
    void *p2 = malloc(required_size);

#ifdef __unix__
    if (malloc_usable_size(p) == malloc_usable_size(p2))
#endif
#ifdef __APPLE__
    if (malloc_size(p) == malloc_size(p2))
#endif
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s%d.MOK %s", FG_GREEN, iTest, RESET_ALL);
        write(1, buffer, strlen(buffer));
    }
    else
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s%d.MKO %s", FG_RED, iTest, RESET_ALL);
        write(1, buffer, strlen(buffer));
    }

    free(p2);
}
