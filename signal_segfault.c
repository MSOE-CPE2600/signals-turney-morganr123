/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Ryan Morgan
 * 
 * Brief summary of modifications:
 * Program that dereferences a null pointer causing a segmentation fault
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Signal handler for SIGSEGV (Segmentation Fault)
void handle_segfault(int sig) {
    printf("Received SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main (int argc, char* argv[]) {
    // Install the signal handler for SIGSEGV
    signal(SIGSEGV, handle_segfault);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);  // This will trigger SIGSEGV

    // Reutnr to exit the program
    return 0;
}