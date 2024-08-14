/*
utils.c

Implementations for helper functions to do with reading and writing.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "utils.h"

struct graphProblem {
  int numServers;
  int numConnections;
  int outageCount;
  int *outageSIDs;
  struct graph *graph;
};

struct graphProblem *readProblem(FILE *outageFile, FILE *networkFile){
  int i;
  int startServer;
  int endServer;
  /* Allocate space for problem specification */
  struct graphProblem *problem = (struct graphProblem *)
    malloc(sizeof(struct graphProblem));
  assert(problem);

  /* First line comprises number of servers and number of connections. */
  assert(fscanf(networkFile, "%d %d", &(problem->numServers),
    &(problem->numConnections)) == 2);

  /* Build graph number of houses + 1 because of datacentre. */
  problem->graph = newGraph(problem->numServers);
  /* Add all edges to graph. */
  for(i = 0; i < problem->numConnections; i++){
    assert(fscanf(networkFile, "%d %d", &startServer, &endServer) == 2);
    addEdge(problem->graph, startServer, endServer);
  }

  /* Read outage information. */
  assert(fscanf(outageFile, "%d", &(problem->outageCount)) == 1);

  problem->outageSIDs = (int *) realloc(NULL, sizeof(int) *
    problem->outageCount);

  /* Allow 0 outages for tasks 2, 3 and 7. */
  if(problem->outageCount > 0){
    assert(problem->outageSIDs);
  }

  for(i = 0; i < problem->outageCount; i++){
    assert(fscanf(outageFile, "%d", &((problem->outageSIDs)[i])) == 1);
  }

  return problem;
}

struct solution *findSolution(struct graphProblem *problem,
  enum problemPart part){
  return graphSolve(problem->graph, part, problem->numServers,
    problem->outageCount, problem->outageSIDs);
}

void freeProblem(struct graphProblem *problem){
  /* No need to free if no data allocated. */
  if(! problem){
    return;
  }
  if(problem->outageSIDs){
    free(problem->outageSIDs);
  }
  freeGraph(problem->graph);
  free(problem);
}

void freeSolution(struct solution *solution){
  /* No need to free if no data allocated. */
  if(! solution){
    return;
  }
  if(solution->largestSubnetSIDs){
    free(solution->largestSubnetSIDs);
  }
  if(solution->postOutageDiameterSIDs){
    free(solution->postOutageDiameterSIDs);
  }
  if(solution->criticalServerSIDs){
    free(solution->criticalServerSIDs);
  }
  free(solution);
}

void initaliseSolution(struct solution *solution){
  if(!solution){
    return;
  }
  solution->connectedSubnets = 0;
  solution->largestSubnet = 0;
  solution->largestSubnetSIDs = NULL;
  solution->postOutageDiameter = 0;
  /* If a path exists, this should be one larger than the diameter. */
  solution->postOutageDiameterCount = 0;
  solution->postOutageDiameterSIDs = NULL;
  solution->criticalServerCount = 0;
  solution->criticalServerSIDs = NULL;
}

int inArray(int value, int* array, int numElem){
  int i;
  
  for (i=0; i < numElem; i++){
    if (array[i] == value){
      return 1;
    }
  } 
  return 0;
}

int maxElem(int *array, int numElem, int startIndex){
  int i, highestElem;
  
  highestElem = array[startIndex];
  for (i=startIndex; i < numElem + startIndex; i++){
    if (array[i] > highestElem){
      highestElem = array[i];
    }
  }
  
  return highestElem;
}

int cmp(const void *a, const void *b){
  return (*(int*) a - *(int*) b);
}