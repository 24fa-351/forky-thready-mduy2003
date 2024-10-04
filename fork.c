#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "fork.h"

void fork_pattern_one(int number_of_processes)
{
    srand(time(NULL));
    pid_t pids[number_of_processes];

    for (int ix = 0; ix < number_of_processes; ++ix)
    {
        pids[ix] = fork(); // Fork a new process

        if (pids[ix] < 0) // Fork failed
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[ix] == 0) // Checks if current process is a child
        {
            printf("Process %d (%d) beginning\n", ix + 1, getpid());
            sleep(1 + (rand() % 8));
            printf("Process %d (%d) exiting\n", ix + 1, getpid());
            exit(EXIT_SUCCESS); // Exit current process
        }
    }

    for (int ix = 0; ix < number_of_processes; ix++) // Waits for all child processes to finish
    {
        pid_t pid = waitpid(pids[ix], 0, 0); // Waits for current process to finish
    }
}

void fork_pattern_two(int number_of_processes)
{
    srand(time(NULL));
    pid_t pid;

    for (int ix = 0; ix < number_of_processes; ++ix)
    {
        pid = fork(); // Fork a new process

        if (pid == 0) // Checks if current process is a child
        {
            // Child process
            printf("Process %d (%d) creating Process %d (%d)\n", ix, getppid(), ix + 1, getpid());
            printf("Process %d (%d) beginning\n", ix + 1, getpid());
            sleep(1 + (rand() % 8));
        }
        else if (pid > 0) // Checks if current process is a parent
        {
            waitpid(pid, 0, 0); // Wait for the child process to finish before exiting
            printf("Process %d (%d) exiting\n", ix, getpid());
            break; // Exit the parent process
        }
        else // Fork failed
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    if (pid == 0) // This is for the last child process to exit
    {
        printf("Process %d (%d) exiting\n", number_of_processes, getpid());
        exit(EXIT_SUCCESS);
    }
}