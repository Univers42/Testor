#ifndef SIGSEGV_H
#define SIGSEGV_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "color.h"

extern int iTest;

void sigsegv(int signal);

#endif
