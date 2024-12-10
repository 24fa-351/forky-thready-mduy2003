#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "fork.h"

void fork_pattern_one(int number_of_processes)
{
    srand(time(NULL));
    pid_t pids[number_of_processes];

    for (int ix = 0; ix < number_of_processes; ++ix) {
        pids[ix] = fork(); // Fork a new process

        if (pids[ix] < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[ix] == 0) { // Child process
            printf("Process %d (%d) beginning\n", ix + 1, getpid());
            sleep(1 + (rand() % 8));
            printf("Process %d (%d) exiting\n", ix + 1, getpid());
            exit(EXIT_SUCCESS);
        }
    }

    // Waits for child processes to finish
    for (int ix = 0; ix < number_of_processes; ix++) {
        pid_t pid = waitpid(pids[ix], 0, 0);
        if (pid < 0) {
            perror("Waitpid failed");
            exit(EXIT_FAILURE);
        }
    }
}

void fork_pattern_two_child(int ix, int number_of_processes)
{
    srand(time(NULL));
    pid_t pid;

    for (; ix < number_of_processes; ++ix) {
        pid = fork(); // Fork a new child

        if (pid == 0) { // Child process
            printf("Process %d (%d) beginning\n", ix + 1, getpid());
            if (ix + 1 < number_of_processes) {
                printf("Process %d (%d) creating Process %d (%d)\n", ix + 1,
                    getpid(), ix + 2, getpid());
            }
            sleep(1 + (rand() % 8));
        } else if (pid > 0) { // Previous child waits
            waitpid(pid, 0, 0);
            printf("Process %d (%d) exiting\n", ix, getpid());
            break;
        } else {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }
}

void fork_pattern_two_parent(int number_of_processes)
{
    pid_t pid = fork(); // Fork the first child process

    if (pid == 0) { // First child process
        printf("Parent process 0 (%d) creating Process 1 (%d)\n", getppid(),
            getpid());
        printf("Process 1 (%d) beginning\n", getpid());
        fork_pattern_two_child(1, number_of_processes);
    } else if (pid > 0) { // Parent process waits for child
        waitpid(pid, 0, 0);
        printf("Parent process (%d) exiting\n", getpid());
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}