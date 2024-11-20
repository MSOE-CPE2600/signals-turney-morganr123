/**
 * File: recv_tennis.c
 * Modified by: Ryan Morgan
 * 
 * Brief summary of program:
 * This program receives the "tennis ball" from serve_tennis then sends it back
 * COMPILE INSTRUCTIONS
 *  1. gcc -o recv_tennis recv_tennis.c
 *  2. gcc -o serve_tennis serve_tennis.c
 *  3. ./recv_tennis
 *  4. in new terminal: pgrep recv_tennis
 *  5. ./serve_tennis <pid of recv_tennis>
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int exchanges = 0;

void signal_handler(int signum, siginfo_t *info, void *context) {
    if (signum == SIGUSR1) {
        // Simulate the player waiting for the ball
        printf("Received the ball from process %d\n", info->si_pid);

        // Wait for a random time between 1 and 2 seconds
        usleep((rand() % 1000000) + 1000000); // Random delay between 1s and 2s

        // Simulate hitting the ball back
        printf("Hitting the ball back to process %d\n", info->si_pid);
        putchar('\007');  // Play the system bell

        // Send the signal back to the sender
        if (exchanges < 10) {
            kill(info->si_pid, SIGUSR1);
            exchanges++;
        } else {
            // End the game after 10 exchanges
            printf("Game over! %d exchanges completed.\n", exchanges);
            exit(0);
        }
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    // Set up the signal handler for SIGUSR1
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);

    // Register the signal handler
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Wait indefinitely to receive signals
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}