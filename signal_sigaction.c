/**
 * File: signal_sigaction.c
 * Modified by: Ryan Morgan
 * 
 * Brief summary of program:
 * recieves a signal for SIGUSR1 and performs the action
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGUSR1
void handle_sigusr1(int sig, siginfo_t *info, void *ucontext) {
    // Print the PID of the process that sent the SIGUSR1 signal
    printf("Received SIGUSR1 from process ID: %d\n", info->si_pid);
    exit(1);
}

int main() {
    struct sigaction sa;

    // Set up the sigaction struct to handle SIGUSR1
    sa.sa_sigaction = handle_sigusr1; // Point to our signal handler
    sa.sa_flags = SA_SIGINFO;          // Use SA_SIGINFO to get additional info

    // Install the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Infinite loop waiting for SIGUSR1 signal
    printf("Waiting for SIGUSR1...\n");
    while (1) {
        // The program will just pause here indefinitely, waiting for signals
        pause();  // Wait for signals
    }

    return 0;
}



