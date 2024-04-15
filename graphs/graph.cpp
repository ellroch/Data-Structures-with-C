#include "graph.h"
#include <cctype>
#include <iostream>
using namespace std;

void initGraph(Graph& g)
{
	g.count = 0;
	g.first = NULL;
}

void deleteGraph(Graph& g)
{
	Vertex* deletePtr;
	Arc* deleteArcPtr;

	while(g.first != NULL)
	{
		deletePtr = g.first;
		while(deletePtr->pArc != NULL)
		{
			deleteArcPtr = deletePtr->pArc;
			deletePtr->pArc = deletePtr->pArc->pNextArc;
			delete deleteArcPtr;
		}
		g.first = g.first->pNextVertex;
		delete deletePtr;
	}
}

bool emptyGraph(Graph& g)
{
	return (g.count == 0);
}

bool graphFull()
{
	Vertex* temp = new Vertex;

	if(temp != NULL)
	{
		delete temp;
		return false;
	}
	return true;
}

int graphCount(Graph& g)
{
	return g.count;
}

int insertVertex(Graph& g, char dataIn)
{
	dataIn = toupper(dataIn);
	Vertex* newPtr;
	Vertex* locPtr;
	Vertex* predPtr;

	newPtr = new Vertex;
	if(newPtr)
	{
		newPtr->pNextVertex = NULL;
		newPtr->data = dataIn;
		newPtr->inDegree = 0;
		newPtr->outDegree = 0;
		newPtr->processed = 0;
		newPtr->pArc = NULL;
		g.count++;
	}
	else // memory overflow
		return -1;

	// Now find insertion point
	locPtr = g.first;
	if(!locPtr) // Empty graph. insert at beginning
		g.first = newPtr;
	else
	{
		predPtr = NULL;
		while(locPtr && dataIn > locPtr->data)
		{
			predPtr = locPtr;
			locPtr = locPtr->pNextVertex;
		}
		if(!predPtr) // Insert before first vertex
			g.first = newPtr;
		else
			predPtr->pNextVertex = newPtr;

		newPtr->pNextVertex = locPtr;
	}
	return 1;
}

int deleteVertex(Graph& g, char dltKey)
{
	dltKey = toupper(dltKey);
	Vertex* predPtr;
	Vertex* walkPtr;

	if(!g.first)
		return -2;

	// Locate vertex to be deleted
	predPtr = NULL;
	walkPtr = g.first;
	while(walkPtr && dltKey > walkPtr->data)
	{
		predPtr = walkPtr;
		walkPtr = walkPtr->pNextVertex;
	}

	if(!walkPtr || dltKey != walkPtr->data)
		return -2;

	// Found vertex. Test degree
	if(walkPtr->inDegree > 0 || walkPtr->outDegree > 0)
		return -1;

	// OK to delete
	if(!predPtr)
		g.first = walkPtr->pNextVertex;
	else
		predPtr->pNextVertex = walkPtr->pNextVertex;

	g.count--;
	delete walkPtr;
	return 1;
}

int insertArc(Graph& g, char fromKey, char toKey)
{
	fromKey = toupper(fromKey);
	toKey = toupper(toKey);

	Arc* newPtr;
	Arc* arcPredPtr;
	Arc* arcWalkPtr;

	Vertex* vertFromPtr;
	Vertex* vertToPtr;

	newPtr = new Arc;
	if(!newPtr)
		return -1;

	// Locate source vertex
	vertFromPtr = g.first;
	while(vertFromPtr && fromKey > vertFromPtr->data)
		vertFromPtr = vertFromPtr->pNextVertex;

	if(!vertFromPtr || fromKey != vertFromPtr->data)
		return -2;

	// Now locate to vertex
	vertToPtr = g.first;
	while(vertToPtr && (toKey > vertToPtr->data))
		vertToPtr = vertToPtr->pNextVertex;

	if(!vertToPtr || toKey != vertToPtr->data)
		return -3;

	// From and to vertices located. Insert new arc.
	vertFromPtr->outDegree++;
	vertToPtr->inDegree++;
	newPtr->destination = vertToPtr;
	if(!vertFromPtr->pArc)
	{
		// Inserting first arc for this vertex
		vertFromPtr->pArc = newPtr;
		newPtr->pNextArc = NULL;
		return 1;
	}

	// Find insertion point in adjacency (arc) list
	arcPredPtr = NULL;
	arcWalkPtr = vertFromPtr->pArc;
	while(arcWalkPtr && toKey >= arcWalkPtr->destination->data)
	{
		arcPredPtr = arcWalkPtr;
		arcWalkPtr = arcWalkPtr->pNextArc;
	}

	if(!arcPredPtr) // Insertion before first arc
		vertFromPtr->pArc = newPtr;
	else
		arcPredPtr->pNextArc = newPtr;

	newPtr->pNextArc = arcWalkPtr;
	return 1;
}

int deleteArc(Graph& g, char fromKey, char toKey)
{
	fromKey = toupper(fromKey);
	toKey = toupper(toKey);

	Vertex* fromVertexPtr;
	Vertex* toVertexPtr;
	Arc* preArcPtr;
	Arc* arcWalkPtr;

	if(!g.first)
		return -2;

	// Locate source vertex
	fromVertexPtr = g.first;
	while(fromVertexPtr && fromKey > fromVertexPtr->data)
		fromVertexPtr = fromVertexPtr->pNextVertex;

	if(!fromVertexPtr || fromKey != fromVertexPtr->data)
		return -2;

	// Locate destination vertex in adjacency list
	if(!fromVertexPtr->pArc)
		return -3;

	preArcPtr = NULL;
	arcWalkPtr = fromVertexPtr->pArc;
	while(arcWalkPtr && toKey > arcWalkPtr->destination->data)
	{
		preArcPtr = arcWalkPtr;
		arcWalkPtr = arcWalkPtr->pNextArc;
	}
	if(!arcWalkPtr || toKey != arcWalkPtr->destination->data)
		return -3;

	toVertexPtr = arcWalkPtr->destination;

	// fromVertex, toVertex, and arcPtr locaetd. Delete arc.
	fromVertexPtr->outDegree--;
	toVertexPtr->inDegree--;
	if(!preArcPtr) // Deleting first arc
		fromVertexPtr->pArc = arcWalkPtr->pNextArc;
	else
		preArcPtr->pNextArc = arcWalkPtr->pNextArc;

	delete arcWalkPtr;
	return 1;
}

int retrieveVertex(Graph& g, char key, Vertex*& dataOut)
{
	key = toupper(key);

	if(g.first == NULL)
		return -2;

	Vertex* locnPtr = g.first;

	while(locnPtr != NULL && key > locnPtr->data)
		locnPtr = locnPtr->pNextVertex;

	if(key == locnPtr->data)
	{
		dataOut = locnPtr;
		return 1;
	}
	else
		return -2;

}

int firstArc(Graph& g, char key, char& destKey)
{
	key = toupper(key);

	if(g.first == NULL)
		return -2;

	Vertex* locnPtr = g.first;

	while(locnPtr != NULL && key > locnPtr->data)
		locnPtr = locnPtr->pNextVertex;

	if(locnPtr != NULL && key == locnPtr->data)
	{
		if(locnPtr->pArc != NULL)
		{
			Arc* toPtr = locnPtr->pArc;
			destKey = toPtr->destination->data;
			return 1;
		}
		else
			return -3;
	}
	else
		return -2;
}

void depthFirst(Graph& g)
{
	bool success;
	Vertex* walkPtr;
	Vertex* vertexPtr;
	Vertex* vertToPtr;
	Stack stack;
	initStack(stack);
	Arc* arcWalkPtr;

	if(!g.first)
		return;

	// Set processed flags to not processed
	walkPtr = g.first;
	while(walkPtr)
	{
		walkPtr->processed = 0;
		walkPtr = walkPtr->pNextVertex;
	}

	// Process each vertex in list
	walkPtr = g.first;
	while(walkPtr)
	{
		if(walkPtr->processed < 2)
		{
			if(walkPtr->processed < 1)
			{
				// Push and set flag to pushed
				success = pushStack(stack, walkPtr);
				if(!success)
					cout << "\aStack overflow 100\a\n", exit(100);

				walkPtr->processed = 1;
			}
		}

		// Process descendents of vertex at stack top
		while(!emptyStack(stack))
		{
			popStack(stack, vertexPtr);
			cout << vertexPtr->data << "\t";
			vertexPtr->processed = 2;

			// Push all vertices from adjacency list
			arcWalkPtr = vertexPtr->pArc;
			while(arcWalkPtr)
			{
				vertToPtr = arcWalkPtr->destination;
				if(vertToPtr->processed == 0)
				{
					success = pushStack(stack, vertToPtr);
					if(!success)
						cout << "\aStack overflow 101\a\n", exit(101);

					vertToPtr->processed = 1;
				}
				arcWalkPtr = arcWalkPtr->pNextArc;
			}
		}
		walkPtr = walkPtr->pNextVertex;
	}
}

void breadthFirst(Graph& g)
{
	bool success;
	Vertex* walkPtr;
	Vertex* vertexPtr;
	Vertex* vertToPtr;
	Arc* arcWalkPtr;
	Queue queue;
	initQueue(queue);

	if(!g.first)
		return;

	// Set processed flags to not processed
	walkPtr = g.first;
	while(walkPtr)
	{
		walkPtr->processed = 0;
		walkPtr = walkPtr->pNextVertex;
	}

	// Process each vertex in list
	walkPtr = g.first;
	while(walkPtr)
	{
		if(walkPtr->processed < 2)
		{
			if(walkPtr->processed < 1)
			{
				// Enqueue and set flag to queue
				success = enqueue(queue, walkPtr);
				if(!success)
					cout << "\aQueue overflow 100\a\n", exit(100);
				walkPtr->processed = 1;
			}
		}

		// process descendents of vertex at queue front
		while(!emptyQueue(queue))
		{
			dequeue(queue, vertexPtr);
			cout << vertexPtr->data << "\t";
			vertexPtr->processed = 2;

			// Enqueue all vertices from adjacency list
			arcWalkPtr = vertexPtr->pArc;
			while(arcWalkPtr)
			{
				vertToPtr = arcWalkPtr->destination;
				if(vertToPtr->processed == 0)
				{
					success = enqueue(queue, vertToPtr);
					if(!success)
						cout << "\aQueue overflow 101\a\n", exit(101);

					vertToPtr->processed = 1;
				}
				arcWalkPtr = arcWalkPtr->pNextArc;
			}
		}
		walkPtr = walkPtr->pNextVertex;
	}
}

void linkedPrint(Graph g)
{
	Vertex* vPtr = g.first;
	Arc* aPtr = NULL;

	while(vPtr != NULL)
	{
		cout << vPtr->data;
		aPtr = vPtr->pArc;

		while(aPtr != NULL)
		{
			cout << " -> " << aPtr->destination->data;
			aPtr = aPtr->pNextArc;
		}

		cout << endl;
		vPtr = vPtr->pNextVertex;
	}
}

bool isDisjoint(Graph g, char key){
	Vertex* vertPtr= g.first;

	if (g.first==NULL)
		return false;

	while (vertPtr->data!=key && vertPtr!=NULL){
		vertPtr=vertPtr->pNextVertex;
	}

	if (vertPtr->inDegree==0 && vertPtr->outDegree==0)
		return true;
	else
		return false;
}

void disjoint(Graph& g, char key){
	Vertex* walkVert=g.first;
	Arc* arcWalker=NULL;
	Arc* arcTrailer=NULL;
	Arc* temp=NULL;
	while(walkVert!=NULL){
		arcTrailer = NULL;
		arcWalker=walkVert->pArc;
		if (walkVert->data==key){
			walkVert->inDegree=0;
			walkVert->outDegree=0;
			arcTrailer=arcWalker;
			while(arcTrailer!=NULL){
				arcWalker=arcWalker->pNextArc;
				delete arcTrailer;
				arcTrailer=arcWalker;
			}
			walkVert->pArc=NULL;
		}
		while(arcWalker!=NULL){
			if (arcWalker->destination->data==key){
				if (arcTrailer==NULL){
					walkVert->pArc=arcWalker->pNextArc;
				}
				else{
					arcTrailer->pNextArc=arcWalker->pNextArc;
				}
				temp= arcWalker;
				arcWalker=arcWalker->pNextArc;
				delete temp;
				walkVert->outDegree-=1;
			}
			else{
			arcTrailer=arcWalker;
			arcWalker=arcWalker->pNextArc;
			}
		}
		walkVert=walkVert->pNextVertex;
	}
}

int getVertexDegree(Graph g, char key){
	Vertex* walker= g.first;
	int degree=-1;
	if (walker==NULL)
		return -1;
	else{
		while(walker!=NULL && degree==-1){
			if(key==walker->data){
				degree= walker->inDegree + walker->outDegree;
			}
			walker=walker->pNextVertex;
		}
	}
	return degree;
}

bool isConnected(Graph g){
	bool connection=true;
	Vertex* walker=g.first;

	if(walker==NULL)
		return connection;

	while(walker!=NULL && connection){
		connection=!isDisjoint(g, walker->data);
		walker=walker->pNextVertex;
	}
	return connection;
}

bool hasIndegree(Graph g, char key){
	bool hasIn=false;
	Vertex* walker=g.first;
	if (walker==NULL)
		return false;
	while(walker->data!=key && walker!=NULL){
		walker=walker->pNextVertex;
	}

	if(walker->inDegree>0)
		hasIn=true;

	return hasIn;
}
