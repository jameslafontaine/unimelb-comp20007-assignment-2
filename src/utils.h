/*
utils.h

Visible structs and functions for helper functions to do with reading and
writing.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
/* Because we use FILE in this file, we should include stdio.h here. */
#include <stdio.h>
/* Because we use struct graph in this file, we should include graph.h here. */
#include "graph.h"
/* The problem specified. */
struct graphProblem;

/* Reads the data from the given file pointer and returns a pointer to this
information. */
struct graphProblem *readProblem(FILE *outageFile, FILE *networkFile);

/* Finds a solution for a given problem. */
struct solution *findSolution(struct graphProblem *problem,
  enum problemPart part);

/* Frees all data used by problem. */
void freeProblem(struct graphProblem *problem);

/* checks whether a given integer is contained in a given array */
int inArray(int value, int* array, int numElems);

/* finds the highest value in an array of integers and returns it */
int maxElem(int *array, int numElem, int startIndex);

/* compares two variables and returns whether a is smaller than, equal to or 
   greater than b */
int cmp(const void *a, const void *b);

