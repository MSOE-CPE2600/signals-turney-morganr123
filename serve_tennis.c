/**
 * File: serve_tennis.c
 * Modified by: Ryan Morgan
 * 
 * Brief summary of program:
 * This program serves a "tennis ball" to recv_tennis and recieves it back in
 * a loop
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
        // Simulate the server receiving the ball
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid_of_receiver>\n", argv[0]);
        exit(1);
    }

    // Get the receiver's process ID (PID) from the command-line argument
    pid_t receiver_pid = atoi(argv[1]);

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

    // Serve the first ball to the receiver
    printf("Serving the ball to process %d\n", receiver_pid);
    putchar('\007');  // Play the system bell
    kill(receiver_pid, SIGUSR1);
    exchanges++;

    // Wait for subsequent signals in the loop
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}