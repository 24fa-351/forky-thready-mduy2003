#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fork.h"

#define SIMULTANEOUS 1
#define SEQUENTIAL 2

int main(int argc, char *argv[])
{
    int min;
    int max;
    int pattern_number;
    sscanf(argv[1], "%d", &min);
    sscanf(argv[2], "%d", &max);
    sscanf(argv[3], "%d", &pattern_number);

    int number_of_processes = max - min + 1;
    if (pattern_number == SIMULTANEOUS)
    {
        fork_pattern_one(number_of_processes);
    } 
    else if (pattern_number == SEQUENTIAL)
    {
        fork_pattern_two(number_of_processes);
    }

    return 0;
}