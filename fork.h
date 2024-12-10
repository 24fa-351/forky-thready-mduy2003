#ifndef FORK_H
#define FORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fork_pattern_one(int number_of_processes);

void fork_pattern_two_parent(int number_of_processes);
void fork_pattern_two_child(int ix, int number_of_processes);

#endif // FORK_H