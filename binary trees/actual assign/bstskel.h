#ifndef BSTSKEL
#define BSTSKEL

struct Node
{
	int value;
	Node* left;
	Node* right;
};

struct QueueNode
{
	Node* treeNode;
	QueueNode* next;
};

struct Queue
{
	QueueNode* head;
	QueueNode* tail;
};

Node* findSmallestBST(Node* root);
Node* findLargestBST(Node* root);
Node* searchBST(Node* root, int argument);
void insertBST(Node*& root, Node* newNode);
bool deleteBST(Node*& root, int dltArgument);
void printBST(Node* root);
void printBSTGraph(/*Your input params*/);

int probe_depth(Node* root, int depth);
void processByQueue(Node* root);

#endif
