#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

#define HEAP_SIZE 15

void reheapUp(int heap[], int newNode)
{
	int parent, hold;

	if(newNode) // not zero indicates not the root.
	{
		parent = (newNode - 1) / 2;
		if(heap[newNode] < heap[parent])
		{
			// Child is greater than parent
			hold = heap[parent];
			heap[parent] = heap[newNode];
			heap[newNode] = hold;
			reheapUp(heap, parent);
		}
	}
}

void reheapDown(int heap[], int root, int last)
{
	int hold, leftKey, rightKey, largeChildKey, largeChildIndex;

	if((root * 2 + 1) <= last)
	{
		// There is at least one child
		leftKey = heap[root * 2 + 1];
		if((root * 2 + 2) <= last)
			rightKey = heap[root * 2 + 2];
		else
			rightKey = -1;

		// Determine which child is larger
		if(leftKey < rightKey)
		{
			largeChildKey = leftKey;
			largeChildIndex = root * 2 + 1;
		}
		else
		{
			largeChildKey = rightKey;
			largeChildIndex = root * 2 + 2;
		}

		// Test if root > larger subtree
		if(heap[root] > largeChildKey)
		{
			// parent < children
			hold = heap[root];
			heap[root] = heap[largeChildIndex];
			heap[largeChildIndex] = hold;
			reheapDown(heap, largeChildIndex, last);
		}
	}
}

bool insertHeap(int heap[], int& last, int data)
{
	if(last == HEAP_SIZE - 1)
		return false;

	last++;
	heap[last] = data;
	reheapUp(heap, last);
	return true;
}

bool deleteHeap(int heap[], int& last, int& dataOut)
{
	if(last < 0)
		return false;

	dataOut = heap[0];
	heap[0] = heap[last];
	last--;
	reheapDown(heap, 0, last);
	return true;
}

void printHeap(int heap[], int root, int heapLast, int level)
{
	int child, i;

	if(root <= heapLast)
	{
		child = (root * 2 + 1);
		printHeap(heap, child + 1, heapLast, level + 1);

		for(i = 0; i < level; i++)
			cout << "    ";

		cout << setw(4) << heap[root] << endl;

		printHeap(heap, child, heapLast, level + 1);
	}
}


int main()
{
	srand(time(NULL));
	int dlt;
	int heap[HEAP_SIZE];
	int heapLast = HEAP_SIZE / 2 - 1;
	int lastIndex = -1; // Passed into insertHeap by reference. Updates in function
	for(int i = 0; i <= heapLast; i++)
	{
		insertHeap(heap, lastIndex, rand()%99 + 1);
	}

	cout << endl;
	printHeap(heap, 0, heapLast, 0);
	cout << endl;

	cout << "Deleting root node:\n\n";
	deleteHeap(heap, heapLast, dlt);

	printHeap(heap, 0, heapLast, 0);

	return 0;
}
