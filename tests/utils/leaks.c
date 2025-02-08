#include "leaks.h"

// Function pointers for the original malloc/free functions
static void *(*libc_malloc)(size_t) = NULL;
static void (*libc_free)(void *) = NULL;

// Tracking for memory allocations
static ptr *mallocList = NULL;  // Pointer to an array of allocated memory
static size_t mallocListCount = 0;  // Number of allocations
static size_t mallocListCapacity = 0;  // Maximum capacity of the mallocList

// Flag to prevent recursion during initialization
static int is_initializing = 0;

// Initialize malloc/free hooks
void mtrace_init(void)
{
    is_initializing = 1;
    libc_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
    libc_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");

    if (!libc_malloc || !libc_free)
    {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}

// Custom malloc implementation
void * malloc(size_t size)
{
    if (!libc_malloc)
        mtrace_init();

    void *p = libc_malloc(size);

    if (!is_initializing)
        mallocListAdd(p, size);

    return p;
}

// Custom free implementation
void free(void *p)
{
    if (!libc_free)
        mtrace_init();

    libc_free(p);
    mallocListRemove(p);
}

// Add an allocation to the malloc list (resize list if needed)
void mallocListAdd(void *p, size_t size)
{
    // Resize the mallocList if capacity is exceeded
    if (mallocListCount >= mallocListCapacity)
    {
        mallocListCapacity = (mallocListCapacity == 0) ? 10 : mallocListCapacity * 2;  // Double the capacity
        mallocList = realloc(mallocList, mallocListCapacity * sizeof(ptr));
        if (!mallocList)
        {
            fprintf(stderr, "Failed to realloc memory for malloc list\n");
            exit(1);
        }
    }

    mallocList[mallocListCount].p = p;
    mallocList[mallocListCount].size = size;
    mallocListCount++;
}

// Remove an allocation from the malloc list
void mallocListRemove(void *p)
{
    for (size_t i = 0; i < mallocListCount; ++i)
    {
        if (mallocList[i].p == p)
        {
            // Shift remaining elements to remove the item
            for (size_t j = i; j < mallocListCount - 1; ++j)
            {
                mallocList[j] = mallocList[j + 1];
            }
            mallocListCount--;
            return;
        }
    }
}

// Show memory leaks (unfreed memory)
void showLeaks(void)
{
    if (mallocListCount > 0)
    {
        write(1, "LEAKS.KO ", 9);

        for (size_t i = 0; i < mallocListCount; ++i)
        {
            char buf[1024];
            int len = snprintf(buf, sizeof(buf), "[%p : %zu] ", mallocList[i].p, mallocList[i].size);
            write(1, buf, len);
        }
        write(1, "\n", 1);
    }
    else
    {
        write(1, "LEAKS.OK\n", 9);
    }

    // Clear the malloc list after showing leaks
    free(mallocList);
    mallocList = NULL;
    mallocListCount = 0;
    mallocListCapacity = 0;
}
