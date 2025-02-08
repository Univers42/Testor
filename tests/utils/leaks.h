#ifndef LEAKS_H
#define LEAKS_H

#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

// Define the ptr struct to store the pointer and size
typedef struct {
    void *p;
    size_t size;
} ptr;

// Functions to manage memory leaks
void * malloc(size_t size);
void free(void * p);
void showLeaks(void);

// Helper functions
void mallocListAdd(void * p, size_t size);
void mallocListRemove(void * p);
void mtrace_init(void);

#endif
