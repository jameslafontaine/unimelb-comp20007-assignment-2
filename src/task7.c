/*
task2.c

Driver function for Problem 1 Task 3.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 2 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"
#include "graph.h"

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Run in the form %s tests/network-t7-1 < outage-t7-1.txt\n",
      argv[0]);
    exit(EXIT_FAILURE);
  }
  /* Read the problem in from stdin (outage info) and argv[1] (network info). */
  FILE *networkFile = fopen(argv[1], "r");
  assert(networkFile);
  struct graphProblem *problem = readProblem(stdin, networkFile);
  assert(fclose(networkFile) == 0);

  /* Find the solution to the problem. */
  struct solution *solution = findSolution(problem, TASK_7);

  /* Report solution */
  printf("The critical servers are: ");
  int i;
  for(i = 0; i < solution->criticalServerCount; i++){
    printf("%d", (solution->criticalServerSIDs)[i]);
    if((i + 1) < solution->criticalServerCount){
      printf(" ");
    }
  }
  printf("\n");

  freeProblem(problem);
  freeSolution(solution);

  return 0;
}

