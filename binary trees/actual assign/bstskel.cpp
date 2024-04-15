#include "bstskel.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
/*
Queue Q;
int* print_arr;
int* nullIndicies;
int currNodeLevel;
int targetIndex;
int len;
Node* next_depth_cue;
*/
Node* findSmallestBST(Node* root)
{
	if(root->left == NULL)
		return root;

	return findSmallestBST(root->left);
}

Node* findLargestBST(Node* root)
{
	if(root->right == NULL)
		return root;
	return findLargestBST(root->right);
}

Node* searchBST(Node* root, int argument)
{
	if(argument<root->left->value){
		return root;
		return searchBST(root->left, argument);
	}
	if(argument>root->right->value){
		return root;
		return searchBST(root->right, argument);
	}

	return root;
}

//Create node outside of function
void insertBST(Node*& root, Node* newNode)
{
	if(root == NULL)
		root = newNode;

	else if(newNode->value < root->value)
		insertBST(root->left, newNode);

	else
		insertBST(root->right, newNode);
}


bool deleteBST(Node*& root, int dltArgument)
{
	if(root == NULL)
		return false;

	else if(dltArgument < root->value)
		return deleteBST(root->left, dltArgument);

	else if(dltArgument > root->value)
		return deleteBST(root->right, dltArgument);

	else
	{
		//Delete Node found--test for leaf node

		Node* dltPtr; // Needed as temporary storage

		if(root->left == NULL)
		{
			dltPtr = root;
			root = root->right;
			delete dltPtr;
			return true;
		}
		else if(root->right == NULL)
		{
			dltPtr = root;
			root = root->left;
			delete dltPtr;
			return true;
		}
		else
		{
			// Node to be deleted not a leaf or leaflike
			// Find largest node in left subtree and replace.
			dltPtr = root->left;
			while(dltPtr->right != NULL)
				dltPtr = dltPtr->right;

			// Node found. Move data and delete leaf node
			root->value = dltPtr->value;

			// Must make recursive call so parent node's
			// pointer is NULL.
			return deleteBST(root->left, dltPtr->value);
		}
	}
}
/*
int probe_depth(Node* root, int depth){
	int l, r;
	if (root->left!=NULL)
		l=probe_depth(root->left, depth+1);
	else
		l=0;
	if(root->right!=NULL)
		r=probe_depth(root->right, depth+1);
	else
		r=0;

	if (left>right)
	 	return l;
	else
		return r;
}

void processByQueue(Node* nextInLine){
	if (nextInLine.treeNode==next_depth_cue){
		currNodeLevel++;
		targetIndex=0;
		if (treeNode->left!=NULL)
			next_depth_cue=nextInLine->treeNode->left;
		else if (treeNode->right!=NULL)
			next_depth_cue=nextInLine->treeNode->right;
		else
			next_depth_cue=NULL
	}
	if (next_depth_cue==NULL){
		if (treeNode->left!=NULL)
			next_depth_cue=nextInLine->treeNode->left;
		if (treeNode->right!=NULL)
			next_depth_cue=nextInLine->treeNode->right;
	}
	for(int counter=0; counter<targetIndex;)
	if (targetIndex==)
	if (nextInLine->treeNode!=NULL)
		print_arr[targetIndex][currNodeLevel]=nextInLine->treeNode->value;

	targetIndex++;
	Q->tail=
}

void printBSTGraph(Node* root)
{
	// probe depth of tree (pass in (int)1)
	int depth=probe_depth(root, 1);
	// declare array len to be (2^depth)-1
	len=(int)pow(2,depth)-1;
	print_arr= new int[len][depth];
	for(int counter=0; counter<len; counter++){
		for(int counter2=0; counter2<depth; counter2++){
			print_arr[counter][counter2];
		}
	}
	//read tree into a queue for breadth first traversal
	Q->head= new QueueNode;
	Q->head->treeNode=root;
	Q->next=NULL;
	Q->tail=root;
	currNodeLevel=0;
	targetIndex=0;
	next_depth_cue=(root->left==NULL ? root->right : root->left);
	nullIndicies= new int[len][2];
	for(counter=0; counter<len; counter++){
		nullIndicies[counter][0]=-1
		nullIndicies[counter][1]=-1
	}

	processByQueue(Q->head);
	//cout << setfill(' ') << setw(3) << ;
}
*/

void printBST(Node* root)
{
	if (root!=NULL){
 	printBST(root->left);
	cout << root->value << "\t";
	printBST(root->right);
	}
	return;
}
