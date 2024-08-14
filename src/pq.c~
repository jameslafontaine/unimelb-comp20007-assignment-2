/*
pq.c

Unsorted Array Implementation

Implementations for helper functions for priority queue construction and
manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdlib.h>
#include <assert.h>

#define INITIALITEMS 32

struct pq {
  int count;
  int allocated;
  void **queue;
  int *priorities;
};


struct pq *newPQ(){
  struct pq *pq = (struct pq *) malloc(sizeof(struct pq));
  assert(pq);
  pq->count = 0;
  pq->allocated = 0;
  pq->queue = NULL;
  pq->priorities = NULL;
  return pq;
}

void enqueue(struct pq *pq, void *item, int priority){
  assert(pq);
  if((pq->count + 1) > pq->allocated){
    if (pq->allocated == 0){
      pq->allocated = INITIALITEMS;
    } else {
      pq->allocated *= 2;
    }
    pq->queue = (void **) realloc(pq->queue, pq->allocated * sizeof(void *));
    assert(pq->queue);
    pq->priorities = (int *) realloc(pq->priorities, pq->allocated *
      sizeof(int));
    assert(pq->priorities);
  }
  (pq->queue)[pq->count] = item;
  (pq->priorities)[pq->count] = priority;
  (pq->count)++;
}

/* Scan through all the priorities linearly and find lowest. */
void *deletemin(struct pq *pq){
  int i;
  int lowestElement = 0;
  void *returnVal;
  if (pq->count <= 0){
    return NULL;
  }
  for(i = 0; i < pq->count; i++){
    if((pq->priorities)[i] < (pq->priorities)[lowestElement]){
      lowestElement = i;
    }
  }
  returnVal = (pq->queue)[lowestElement];
  /* Delete item from queue by swapping final item into place of deleted
    element. */
  if(pq->count > 0){
    (pq->priorities)[lowestElement] = (pq->priorities)[pq->count - 1];
    (pq->queue)[lowestElement] = (pq->queue)[pq->count - 1];
    (pq->count)--;
  }
  return returnVal;
}

int empty(struct pq *pq){
  return pq->count == 0;
}

void freePQ(struct pq *pq){
  if(! pq) {
    return;
  }
  if(pq->allocated > 0){
    free(pq->queue);
    free(pq->priorities);
  }
  free(pq);
}
