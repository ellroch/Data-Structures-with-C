#include "bstskel.h"
#include <iostream>
#include <ctime>
using namespace std;

//declared a global variable (int *)in bstskel.h and defined in bstskel.cpp
//also a function used to determine the depth of the tree is called in the print function



int main()
{
	srand(time(NULL));
	Node* root = NULL;
	Node* newNode = NULL;

	for(int i = 0; i < 10; i++)
	{
		newNode = new Node;

		newNode->left = NULL;
		newNode->right = NULL;
		newNode->value = rand()%100;


		insertBST(root, newNode);
	}

	printBST(root); // breadth first
	cout << endl;

	//printBSTGraph(/*Your input params*/);

	cout << endl;
	int dlt;
	cout << "Delete: ";
	cin >> dlt;

	deleteBST(root, dlt);
	printBST(root);


	return 0;
}
