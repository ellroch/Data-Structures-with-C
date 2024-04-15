#ifndef VERTEX_H
#define VERTEX_H

struct Vertex;
struct Arc;
struct Node;

struct Vertex
{
	Vertex* pNextVertex;
	char data;
	int inDegree;
	int outDegree;
	short processed;
	Arc* pArc;
};

struct Arc
{
	Vertex* destination;
	Arc* pNextArc;
};

struct Node
{
	Vertex* data;
	Node* next;
};

#endif