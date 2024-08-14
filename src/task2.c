/*
task2.c

Driver function for Problem 1 Task 2.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 2 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"
#include "graph.h"

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Run in the form %s tests/network-t2-1 < outage-t2-1.txt\n",
      argv[0]);
    exit(EXIT_FAILURE);
  }
  /* Read the problem in from stdin (outage info) and argv[1] (network info). */
  FILE *networkFile = fopen(argv[1], "r");
  assert(networkFile);
  struct graphProblem *problem = readProblem(stdin, networkFile);
  assert(fclose(networkFile) == 0);

  /* Find the solution to the problem. */
  struct solution *solution = findSolution(problem, TASK_2);

  /* Report solution */
  printf("Before the outage, the number of connected subnetworks is: %d\n",
    solution->connectedSubnets);

  freeProblem(problem);
  freeSolution(solution);

  return 0;
}

