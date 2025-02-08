#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "sigsegv.h"  // Assuming the header is C-compatible
#include "check.h"    // Assuming this header is C-compatible
#include "gnl.h"      // Assuming this header is C-compatible

extern int iTest;  // Variable to track test number
extern _Bool is_initializing;  // Use _Bool for boolean in C

void title(const char *s) {
    write(1, s, strlen(s));  // C's way of writing a string to stdout
}

int main(void)
{
    is_initializing = 0;  // False equivalent in C
    
    // Set up signal handler for segmentation faults
    signal(SIGSEGV, sigsegv);

    int fd[4];
    
    // Print title with buffer size information
    title("[BUFFER_SIZE = ");  // Printing buffer size
    printf("%d", BUFFER_SIZE);  // Assuming BUFFER_SIZE is an integer
    title("]: \n");

    title("multiple fd: ");
    
    // Open the file descriptors for testing
    fd[0] = open("files/41_with_nl", O_RDWR);
    if (fd[0] == -1) {
        perror("Error opening file 41_with_nl");
        return 1;  // Exit if file cannot be opened
    }
    
    /* 1 */ gnl(1000, NULL);
    /* 2 */ gnl(fd[0], "0123456789012345678901234567890123456789\n");

    fd[1] = open("files/42_with_nl", O_RDWR);
    if (fd[1] == -1) {
        perror("Error opening file 42_with_nl");
        return 1;
    }
    
    /* 3 */ gnl(1001, NULL);
    /* 4 */ gnl(fd[1], "01234567890123456789012345678901234567890\n");

    fd[2] = open("files/43_with_nl", O_RDWR);
    if (fd[2] == -1) {
        perror("Error opening file 43_with_nl");
        return 1;
    }
    
    /* 5 */ gnl(1002, NULL);
    /* 6 */ gnl(fd[2], "012345678901234567890123456789012345678901\n");

    /* 7 */ gnl(1003, NULL);
    /* 8 */ gnl(fd[0], "0");

    /* 9 */ gnl(1004, NULL);
    /* 10 */ gnl(fd[1], "1");

    /* 11 */ gnl(1005, NULL);
    /* 12 */ gnl(fd[2], "2");

    /* 13 */ gnl(fd[0], NULL);
    /* 14 */ gnl(fd[1], NULL);
    /* 15 */ gnl(fd[2], NULL);
    
    // Call to show memory leaks (assuming the function is defined correctly for C)
    showLeaks();

    fd[3] = open("files/nl", O_RDWR);
    if (fd[3] == -1) {
        perror("Error opening file nl");
        return 1;
    }
    
    /* 16 */ gnl(1006, NULL);
    /* 17 */ gnl(fd[3], "\n");
    /* 18 */ gnl(1007, NULL);
    /* 19 */ gnl(fd[3], NULL);
    
    showLeaks();
    write(1, "\n", 1);  // Output new line for clarity

    // Closing all file descriptors
    for (int i = 0; i < 4; i++) {
        close(fd[i]);
    }

    return 0;
}
