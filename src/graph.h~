/*
graph.h

Visible structs and functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021 and
  modified for Assignment 2 2021
*/

/* Definition of a graph. */
struct graph;

enum problemPart;

struct solution;

/* A particular solution to a graph problem. */
#ifndef SOLUTION_STRUCT
#define SOLUTION_STRUCT
struct solution {
  int connectedSubnets;
  int largestSubnet;
  int *largestSubnetSIDs;
  int postOutageDiameter;
  int postOutageDiameterCount;
  int *postOutageDiameterSIDs;
  int criticalServerCount;
  int *criticalServerSIDs;
};
#endif

/* Which part the program should find a solution for. */
#ifndef PART_ENUM
#define PART_ENUM
enum problemPart {
  TASK_2=0,
  TASK_3=1,
  TASK_4=2,
  TASK_7=3
};
#endif

/* Creates an undirected graph with the given numVertices and no edges and
returns a pointer to it. NumEdges is the number of expected edges. */
struct graph *newGraph(int numVertices);

/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end);

/* Finds:
  - Number of connected subnetworks (before outage) (Task 2)
  - Number of servers in largest subnetwork (before outage) (Task 3)
  - SIDs of servers in largest subnetwork (before outage) (Task 3)
  - Diameter of largest subnetworks (after outage) (Task 4)
  - Number of servers in path with largest diameter - should be one more than
    Diameter if a path exists (after outage) (Task 4)
  - SIDs in largest subnetwork (after outage) (Task 4)
  - Number of critical servers (before outage) (Task 7)
  - SIDs of critical servers (before outage) (Task 7)
 */
struct solution *graphSolve(struct graph *g, enum problemPart part,
  int numServers, int numOutages, int *outages);

/* Frees all memory used by graph. */
void freeGraph(struct graph *g);

/* Sets all values to initial values so free can work for all tasks without
  change. */
void initaliseSolution(struct solution *solution);

/* Frees all data used by solution. */
void freeSolution(struct solution *solution);



