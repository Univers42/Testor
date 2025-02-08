#include "sigsegv.h"
#include "color.h"

extern int iTest;

void sigsegv(int signal)
{
    (void)signal;
    printf("%s%d.SIGSEGV%s\n", FG_LYELLOW, iTest++, RESET_ALL);
    exit(EXIT_SUCCESS);
}
