#include "graph.h"
#include <iostream>
using namespace std;

int main()
{
	Graph g;
	initGraph(g);

	insertVertex(g, 'A');
	insertVertex(g, 'B');
	insertVertex(g, 'C');
	insertVertex(g, 'D');
	insertVertex(g, 'E');
	insertVertex(g, 'F');

	insertArc(g, 'A', 'B');
	insertArc(g, 'B', 'C');
	insertArc(g, 'B', 'E');
	insertArc(g, 'C', 'E');
	insertArc(g, 'C', 'D');
	insertArc(g, 'E', 'D');
	insertArc(g, 'E', 'F');

	cout << "Depth First Traversal:\n";
	depthFirst(g);

	cout << "\n\nBreadthFirst Traversal:\n";
	breadthFirst(g);

	cout << "\n\nLinkedList Representation:\n";

	linkedPrint(g);

	bool temp= hasIndegree(g,'A');
	cout << "\n\nA hasIndegree:" << temp;
	temp= hasIndegree(g,'D');
	cout << "\nD hasIndegree:" << temp;

	temp= isDisjoint(g, 'D');
	cout << "\nD isDisjoint: " << temp;

	disjoint(g, 'C');
	linkedPrint(g);


	int degree =	getVertexDegree(g,'C');
	cout << "\nC vertexDegree: " << degree;

	temp= isConnected(g);
	cout << "isConnected: " << temp;

	deleteGraph(g);

	return 0;
}
