/*
graph.c

Set of vertices and edges implementation.

Implementations for helper functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "graph.h"
#include "utils.h"
#include "pq.h"

#define INITIALEDGES 32
#define MAXVERTICES 32
#define TRUE 1
#define FALSE 0

struct edge;

/* Definition of a graph. */
struct graph {
  int numVertices;
  int numEdges;
  int allocedEdges;
  struct edge **edgeList;
};

/* Definition of an edge. */
struct edge {
  int start;
  int end;
};

struct pq {
  int count;
  int allocated;
  void **queue;
  int *priorities;
};

/* Visits all vertices in a connected component using DFS */

void DFSExplore(int mark[], int v, int numEdges, struct edge **edgeList, 
	            int *currentSubnet, int currentSubnetSIDs[]);

void DFSExploreOutage(int mark[], int v, int numEdges, struct edge **edgeList, 
	int *currentSubnet, int currentSubnetSIDs[], int *outages, int numOutages);

void DFSExploreCritical(int mark[], int v, int numEdges, struct edge **edgeList, 
	            int parent[], int HRA[], int *count);


struct graph *newGraph(int numVertices){
  struct graph *g = (struct graph *) malloc(sizeof(struct graph));
  assert(g);
  /* Initialise edges. */
  g->numVertices = numVertices;
  g->numEdges = 0;
  g->allocedEdges = 0;
  g->edgeList = NULL;
  return g;
}

/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end){
  assert(g);
  struct edge *newEdge = NULL;
  /* Check we have enough space for the new edge. */
  if((g->numEdges + 1) > g->allocedEdges){
    if(g->allocedEdges == 0){
      g->allocedEdges = INITIALEDGES;
    } else {
      (g->allocedEdges) *= 2;
    }
    g->edgeList = (struct edge **) realloc(g->edgeList,
      sizeof(struct edge *) * g->allocedEdges);
    assert(g->edgeList);
  }

  /* Create the edge */
  newEdge = (struct edge *) malloc(sizeof(struct edge));
  assert(newEdge);
  newEdge->start = start;
  newEdge->end = end;

  /* Add the edge to the list of edges. */
  g->edgeList[g->numEdges] = newEdge;
  (g->numEdges)++;
}

/* Frees all memory used by graph. */
void freeGraph(struct graph *g){
  int i;
  for(i = 0; i < g->numEdges; i++){
    free((g->edgeList)[i]);
  }
  if(g->edgeList){
    free(g->edgeList);
  }
  free(g);
}

/* Finds:
  - Number of connected subnetworks (before outage) (Task 2)
  - Number of servers in largest subnetwork (before outage) (Task 3)
  - SIDs of servers in largest subnetwork (before outage) (Task 3)
  - Diameter of largest subnetworks (after outage) (Task 4)
  - Number of servers in path with largest diameter - should be one more than
    Diameter if a path exists (after outage) (Task 4)
  - SIDs in path with largest diameter (after outage) (Task 4)
  - Number of critical servers (before outage) (Task 7)
  - SIDs of critical servers (before outage) (Task 7)
*/
struct solution *graphSolve(struct graph *g, enum problemPart part,
  int numServers, int numOutages, int *outages){

  struct solution *solution = (struct solution *)
    malloc(sizeof(struct solution));
  
  int v, i;
  assert(solution);
  /* Initialise solution values */
  initaliseSolution(solution);
  if(part == TASK_2){
    /* IMPLEMENT TASK 2 SOLUTION HERE */
    
    solution->connectedSubnets = 0;
    int mark[MAXVERTICES] = {0};
    
    int currentSubnet = 0;
    int currentSubnetSIDs[MAXVERTICES] = {0};
    
    int count = 0;
    for (v=0; v < numServers; v++){
      // check if this vertex has been visited
      if (!mark[v]){
      	// we have found a subnetwork and will now traverse it using DFS
        count += 1;
        DFSExplore(mark, v, g->numEdges, g->edgeList, &currentSubnet, 
        	                                                 currentSubnetSIDs);
      }
    }
    solution->connectedSubnets = count;
    
  } else if(part == TASK_3) {
    /* IMPLEMENT TASK 3 SOLUTION HERE */
    solution->largestSubnet = 0;
    solution->largestSubnetSIDs = NULL;
    
    solution->largestSubnetSIDs = (int*)malloc(numServers * sizeof(int));
    
    solution->largestSubnetSIDs[0] = MAXVERTICES;
 
    int mark[MAXVERTICES] = {0};
    int currentSubnet;
    int currentSubnetSIDs[MAXVERTICES] = {0};

    int count = 0;
    for (v=0; v < numServers; v++){
      // check if this vertex has been visited
      if (!mark[v]){
      	// we have found a subnetwork and will now traverse it using DFS
        count += 1;
        currentSubnet = 0;
        DFSExplore(mark, v, g->numEdges, g->edgeList, &currentSubnet, 
        	       currentSubnetSIDs);
        // reorder largestSubnetSIDs to be in increasing order
        qsort(currentSubnetSIDs, currentSubnet, sizeof(int), cmp); 
        
        if (currentSubnet > solution->largestSubnet){
          solution->largestSubnet = currentSubnet;
          for (i=0; i < currentSubnet; i++){
            solution->largestSubnetSIDs[i] = currentSubnetSIDs[i];
          }
        /* if two subnets have the same size then choose the one with the
        lower SID */
        }else if (currentSubnet == solution->largestSubnet && 
        	       currentSubnetSIDs[0] < (solution->largestSubnetSIDs)[0]){
          for (i=0; i < currentSubnet; i++){
            solution->largestSubnetSIDs[i] = currentSubnetSIDs[i];
          }
        }
      }
    }
  } else if(part == TASK_4) {
    /* IMPLEMENT TASK 4 SOLUTION HERE */
    solution->postOutageDiameter = 0;
    solution->postOutageDiameterCount = 0;
    solution->postOutageDiameterSIDs = NULL;
    
    solution->postOutageDiameterSIDs = (int*)malloc(numServers * sizeof(int));
    solution->postOutageDiameterSIDs[0] = MAXVERTICES;
   
    
    solution->largestSubnet = 0;
    solution->largestSubnetSIDs = NULL;
    solution->largestSubnetSIDs = (int*)malloc(numServers * sizeof(int));
    solution->largestSubnetSIDs[0] = MAXVERTICES;
    
    int currentSubnet;
    int currentSubnetSIDs[MAXVERTICES] = {0};
    int mark[MAXVERTICES] = {0};
    
    int count = 0;
    
    for (v=0; v < numServers; v++){
      // check if this vertex has been visited
      if (!mark[v]){
      	// we have found a subnetwork and will now traverse it using DFS
        count += 1;
        currentSubnet = 0;
        DFSExploreOutage(mark, v, g->numEdges, g->edgeList, &currentSubnet, 
        	       currentSubnetSIDs, outages, numOutages);
        // reorder largestSubnetSIDs to be in increasing order
        qsort(currentSubnetSIDs, currentSubnet, sizeof(int), cmp); 
        
        if (currentSubnet > solution->largestSubnet){
          solution->largestSubnet = currentSubnet;
          for (i=0; i < currentSubnet; i++){
            solution->largestSubnetSIDs[i] = currentSubnetSIDs[i];
          }
        /* if two subnets have the same size then choose the one with the
        lower SID */
        }else if (currentSubnet == solution->largestSubnet && 
        	       currentSubnetSIDs[0] < (solution->largestSubnetSIDs)[0]){
          for (i=0; i < currentSubnet; i++){
            solution->largestSubnetSIDs[i] = currentSubnetSIDs[i];
          }
        }
      }
    }

    /* perform Dijkstra's Algorithm to find the longest shortest path */
    int v_initial = solution->largestSubnetSIDs[0];
    
    int dist[MAXVERTICES];
    int prev[MAXVERTICES];
    int vertices[MAXVERTICES];
    
    for (v=v_initial; v < v_initial + solution->largestSubnet; v++){
      dist[v] = INT_MAX;
      prev[v] = -1;
      vertices[v] = v;
    }
    dist[v_initial] = 0;
    struct pq *pq = newPQ();
    for(v=v_initial; v < v_initial + solution->largestSubnet; v++){
      enqueue(pq, (void*)&(vertices[v]), dist[v]);
    }
    while (!empty(pq)){
      int u = *(int*)deletemin(pq);
      for (i=0; i < g->numEdges; i++){
  	    if (g->edgeList[i]->start == u){
          int w = g->edgeList[i]->end;
          if (isinPQ(pq, &w) && dist[u] + 1 < dist[w]){
            dist[w] = dist[u] + 1;
            prev[w] = u;
            updatePQ(pq, &w, dist[w]);
          }
        // check (w, u) too as this is an undirected graph
        }else if (g->edgeList[i]->end == u){
          int w = g->edgeList[i]->start;
          if (isinPQ(pq, &w) && dist[u] + 1 < dist[w]){
            dist[w] = dist[u] + 1;
            prev[w] = u;
            updatePQ(pq, &w, dist[w]);
          }
        }
      }	
    }
    
    /* find the highest value in dist array (diameter) and use this to find the 
       path with the smallest starting and ending server SID */
    solution->postOutageDiameter = maxElem(dist, solution->largestSubnet, 
    	                                                             v_initial);
    int endVertex = INT_MAX;
    for (v=v_initial; v < v_initial + solution->largestSubnet; v++){
      if (dist[v] == solution->postOutageDiameter && v < endVertex){
        endVertex = v;
      }
    }
    
    /* Now rebuild the path via the prev array */
    v = endVertex;
    while (v != -1){
      (solution->postOutageDiameterSIDs)[solution->postOutageDiameterCount] = v;
      // printf("Solution added to postOutageDiameterSIDs\n");
      v = prev[v];
      solution->postOutageDiameterCount += 1;
    }
    
    /* reorder the SIDs into ascending order */
    qsort(solution->postOutageDiameterSIDs, solution->postOutageDiameterCount, 
    	                                                      sizeof(int), cmp);
        
    
    
  } else if(part == TASK_7) {
    /* IMPLEMENT TASK 7 SOLUTION HERE */
    solution->criticalServerCount = 0;
    solution->criticalServerSIDs = NULL;
    
    solution->criticalServerSIDs = (int*)malloc(numServers * sizeof(int));
    
    int mark[MAXVERTICES] = {0}; 
    int parent[MAXVERTICES];
    int HRA[MAXVERTICES];
    
    for (v=0; v < numServers; v++){
      parent[v] = -1;
      HRA[v] = v;
    }
    
    int count = 0;
    for (v=0; v < numServers; v++){
      // check if this vertex has been visited
      if (!mark[v]){
      	// we have found a subnetwork and will now traverse it using DFS
        DFSExploreCritical(mark, v, g->numEdges, g->edgeList, parent, HRA, 
        	                                                           &count);
      }
    }
    /* now iterate through the parent array to find the critical vertices */
    for (v=0; v < numServers; v++){
      // add root vertices with more than one child to the list
      if (parent[v] == -1){
      	  int children = 0;
      	  for (i=0; i < numServers; i++){
      	    if (parent[i] == v){
      	      children += 1;
      	    }
      	  }
      	  if (children > 1){
      	    solution->criticalServerSIDs[solution->criticalServerCount] = v;
      	    solution->criticalServerCount += 1;
          }
      // add non-root vertices v whose child's HRA push order >= push order of v
      }else if (mark[HRA[v]] >= mark[parent[v]] && parent[parent[v]] != -1 && 
      	  !inArray(parent[v], solution->criticalServerSIDs, 
      	  	                                    solution->criticalServerCount)){
        solution->criticalServerSIDs[solution->criticalServerCount] = parent[v];
        solution->criticalServerCount += 1;
      }   
    }
  }
  return solution;
}

void DFSExplore(int mark[], int v, int numEdges, struct edge **edgeList, 
	int *currentSubnet, int currentSubnetSIDs[]){ 
  int i, w;
  
  // this vertex has now been visited so we mark it
  mark[v] = 1;
  currentSubnetSIDs[*currentSubnet] = v;
  *currentSubnet += 1;
  
  // check if w has been visited for all edges (v, w)
  for (i=0; i < numEdges; i++){
  	if (edgeList[i]->start == v){
      w = edgeList[i]->end;
      if (!mark[w]){
        // if w hasn't been visited we will visit it and continue traversing
        DFSExplore(mark, w, numEdges, edgeList, currentSubnet, 
        	       currentSubnetSIDs);
      }
    // check (w, v) too as this is an undirected graph
    }else if (edgeList[i]->end == v){
       w = edgeList[i]->start;
      if (!mark[w]){
        // if w hasn't been visited we will visit it and continue traversing
        DFSExplore(mark, w, numEdges, edgeList, currentSubnet, 
        	       currentSubnetSIDs);
      }	
    }
  }
  return;
}

void DFSExploreOutage(int mark[], int v, int numEdges, struct edge **edgeList, 
	int *currentSubnet, int currentSubnetSIDs[], int *outages, int numOutages){
  int i, w;
  
  // this vertex has now been visited so we mark it
  mark[v] = 1;
  currentSubnetSIDs[*currentSubnet] = v;
  *currentSubnet += 1;
  
  // check if w has been visited for all edges (v, w)
  for (i=0; i < numEdges; i++){
  	if (edgeList[i]->start == v && !inArray(v, outages, numOutages) && 
  		!inArray(edgeList[i]->end, outages, numOutages)){
      w = edgeList[i]->end;
      if (!mark[w]){
        // if w hasn't been visited we will visit it and continue traversing
        DFSExploreOutage(mark, w, numEdges, edgeList, currentSubnet, 
        	       currentSubnetSIDs, outages, numOutages);
      }
    // check (w, v) too as this is an undirected graph
    }else if (edgeList[i]->end == v && !inArray(v, outages, numOutages) && 
    	      !inArray(edgeList[i]->start, outages, numOutages)){
       w = edgeList[i]->start;
      if (!mark[w]){
        // if w hasn't been visited we will visit it and continue traversing
        DFSExploreOutage(mark, w, numEdges, edgeList, currentSubnet, 
        	       currentSubnetSIDs, outages, numOutages);
      }	
    }
  }
  return;

}

void DFSExploreCritical(int mark[], int v, int numEdges, struct edge **edgeList, 
	                    int parent[], int HRA[], int *count){ 
  int i, j, w;
  
  // this vertex has now been visited so we mark it
  *count += 1;
  mark[v] = *count;
  
  // check if w has been visited for all edges (v, w)
  for (i=0; i < numEdges; i++){
  	if (edgeList[i]->start == v){
      w = edgeList[i]->end;
      if (!mark[w]){
        parent[w] = v;
        // if w hasn't been visited we will visit it and continue traversing
        DFSExploreCritical(mark, w, numEdges, edgeList, parent, HRA, count);
      }else if(mark[HRA[w]] < mark[v] && w != parent[v]){
        HRA[v] = w;
        j = parent[v];
        while (mark[HRA[v]] < mark[HRA[j]]){
          HRA[j] = HRA[v];
          j = parent[j];
        }
      }
    // check (w, v) too as this is an undirected graph
    }else if (edgeList[i]->end == v){
      w = edgeList[i]->start;
      if (!mark[w]){
        parent[w] = v;
        // if w hasn't been visited we will visit it and continue traversing
        DFSExploreCritical(mark, w, numEdges, edgeList, parent, HRA, count);   
      }else if(mark[HRA[w]] < mark[v] && w != parent[v]){
        HRA[v] = w;
        j = parent[v];
        /* update all ancestors' HRA if its HRA push order is larger than the
        push order of the descendant's HRA */
        while (mark[HRA[v]] < mark[HRA[j]]){
          HRA[j] = HRA[v];
          j = parent[j];
        }
      }
    }
  }
  return;
}

