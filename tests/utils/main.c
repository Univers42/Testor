#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include "sigsegv.h"
#include "gnl.h"
#include "color.h"

int iTest = 1;

int main() {
    // Open a test file for reading
    int fd = open("test_file.txt", O_RDONLY);  
    if (fd == -1) {
        perror("Error opening file");
        return 1;  // Exit if the file cannot be opened
    }

    // Run the test (gnl function should handle the actual reading and comparing)
    TEST(gnl(fd, "Expected output"));

    // Set up the signal handler for SIGSEGV (this is for the test case where we force a segfault)
    signal(SIGSEGV, sigsegv);

    // Force a segmentation fault by dereferencing a NULL pointer (for testing purposes)
    int *ptr = NULL;
    *ptr = 42;  // This will cause a SIGSEGV

    // Memory allocation check
    char *str = malloc(100);  // Allocate memory for testing
    if (str == NULL) {
        perror("Memory allocation failed");
        return 1;  // Exit if memory allocation failed
    }
    check(str != NULL);  // Check if memory was successfully allocated

    // Perform memory size check (assuming 100 bytes is expected)
    mcheck(str, 100);

    // Clean up: Free the allocated memory
    free(str);
    
    // Close the file descriptor
    close(fd);

    // Increment the test counter for the next test
    iTest++;

    return 0;  // Return success
}
