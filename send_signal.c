/**
 * File: send_signal.c
 * Modified by: Ryan Morgan
 * 
 * Brief summary of program:
 * This program sends a random integer to the designated pid
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    // Get the target process ID (PID) from command-line argument
    pid_t pid = atoi(argv[1]);

    if (pid <= 0) {
        fprintf(stderr, "Invalid PID: %d\n", pid);
        return 1;
    }

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random integer
    int random_value = rand();

    // Print the random integer before sending it
    printf("Sending SIGUSR1 with value: %d to PID: %d\n", random_value, pid);

    // Create a sigval structure to hold the random integer
    union sigval value;
    value.sival_int = random_value;

    // Send the signal with the integer to the target PID
    if (sigqueue(pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return 1;
    }

    return 0;
}
