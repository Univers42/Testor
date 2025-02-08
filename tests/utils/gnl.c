#include "gnl.h"
#include "color.h"
#include "check.h"
#include "get_next_line.h"  // Assumed this is already converted to C
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

extern int iTest;

void gnl(int fd, const char *expectedReturn)
{
    char *gnlReturn = get_next_line(fd);
    if (expectedReturn == NULL) {
        check(gnlReturn == NULL);
    } else {
        check(gnlReturn && strcmp(gnlReturn, expectedReturn) == 0);
    }
    free(gnlReturn);
    iTest++;
}
