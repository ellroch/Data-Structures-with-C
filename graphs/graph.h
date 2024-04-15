#ifndef GRAPH_H
#define GRAPH_H
#include "queue.h"
#include "stack.h"
#include "vertex.h"

struct Graph
{
	int count;
	Vertex* first;
};

void initGraph(Graph& g);
void deleteGraph(Graph& g);
int insertVertex(Graph& g, char dataIn);
int deleteVertex(Graph& g, char dltKey);
int insertArc(Graph& g, char fromKey, char toKey);
int deleteArc(Graph& g, char fromKey, char toKey);
int retrieveVertex(Graph& g, char key, Vertex*& dataOut);
int firstArc(Graph& g, char key, char& destKey);
bool emptyGraph(Graph& g);
bool graphFull();
int graphCount(Graph& g);
void depthFirst(Graph& g);
void breadthFirst(Graph& g);
void linkedPrint(Graph g);

//For you to implement
bool isDisjoint(Graph g, char key);
void disjoint(Graph& g, char key);
int getVertexDegree(Graph g, char key);
bool isConnected(Graph g);
bool hasIndegree(Graph g, char key);

#endif
