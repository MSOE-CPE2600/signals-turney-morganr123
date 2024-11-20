/**
 * File: signal_alarm.c
 * Modified by: Ryan Morgan
 * 
 * Brief summary of program:
 * Signal handler for SIGALRM - prints a message when the alarm signal is received
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handle_alarm(int sig) {
    printf("SIGALRM received: Time's up!\n");
}

int main() {
    // Register the signal handler for SIGALRM
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(1);
    }

    // Set an alarm to trigger in 5 seconds
    printf("Setting alarm for 5 seconds...\n");
    alarm(5);

    // Wait for the signal to be delivered
    printf("Waiting for SIGALRM to be received...\n");
    pause();  // The process will pause here until a signal is received

    return 0;
}