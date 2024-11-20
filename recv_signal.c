/**
 * File: recv_signal.c
 * Modified by: Ryan Morgan
 * 
 * Brief summary of program:
 * this program receives the information from a signal sent to it
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void signal_handler(int signum, siginfo_t *info, void *context) {
    if (signum == SIGUSR1) {
        // Retrieve and print the integer passed with SIGUSR1
        printf("Received signal SIGUSR1 with value: %d\n", info->si_value.sival_int);
        exit(1);
    }
}

int main() {
    struct sigaction sa;
    
    // Setup the sigaction structure
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;  // This tells sigaction to use the signal info
    sa.sa_sigaction = signal_handler;  // Register the handler function

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Wait in an infinite loop (the program stays alive to catch signals)
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}
