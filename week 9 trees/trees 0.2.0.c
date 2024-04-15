//-------------------------------------------------------preprocessor
#include <stdio.h>
#include <stddef.h>
#include <string.h>
typedef struct treeNode{
	struct treeNode *left;
	char data;
	struct treeNode *right;
	} Branch;

typedef Branch *BranchPtr;

//------------------------------------------------------- prototypes
void get_name(char **fileNamePtr);//just copy pasta'd this function from the last assignment +some small changes
void preorder(BranchPtr currNode);
void inorder(BranchPtr currNode);
void postorder(BranchPtr currNode);
void freeTheTree(BranchPtr currNode);
void checkTree(BranchPtr currNode);
void insert(BranchPtr *rootPtr, char **fileNamePtr);
//------------------------------------------------------- main func
int main(){
	char *fileName;
    BranchPtr root= NULL;
	char trash[3];
	int menu= 1;
	
	while (menu!=0){
				//                              //                   //                          //                                 //                                //                             
		printf("what would you like to do:\n%5s(0) end program \n%5s(1) grow a letter tree \n%5s(2) read the tree (pre-order) \n%5s(3) read the tree (in-order) \n%5s(4) read the tree (post-order) \n%5s(5) scan the tree for a character \n\n%5s: ","","","","","","","");
		scanf("%d",&menu);
		fgets(trash,3,stdin);
		
		switch (menu){
			case 0:// end program (free the tree)
					freeTheTree(root);
				break;
			
			case 1:// grow a letter tree (insert)
				get_name(&fileName);
				insert(&root,&fileName);
				break;
			
			case 2:// preorder
				preorder(root);
				printf("\n");
				break;
			
			case 3:// inorder
				inorder(root);
				printf("\n");
				break;
			
			case 4:// postorder
				postorder(root);
				printf("\n");
				break;
				
			case 5:// checkTree
				checkTree(root);
				printf("\n");
				break;
			default:// print "there was a problem processing that request"
				printf("there was a problem processing that request\n");
				break;
		}
		
	}
	
	return 0;
}
//------------------------------------------------------- check tree func
void checkTree(BranchPtr currNode){
	BranchPtr temp= *rootPtr;
	char hold;
	int sentinal=0;
	unsigned int copies= 0;
	int sentinal_dup=0;
	
	printf("%4s what character should we check for (searching for a space " " will end the search)\n%5s: ","","");
	hold= fgetc(stdin);
	
	while (hold!=32){
		
		sentinal=0;
		temp=*rootPtr;
		
		while (sentinal==0){
			if (*rootPtr==NULL){
					printf("the tree is currently empty\n");
					sentinal=1;
				}
				else {
					printf("no more memory! (there was a problem allocating memory for the last node!)\n");
				}
			}
			else {
				while(sentinal==0){
					if (temp->data == hold){
						printf("MATCH FOUND!");
						sentinal= 1;
						sentinal_dup=1;
					
					}
					
					if (hold < temp->data){
						if (temp->left==NULL){
							printf("No duplicates were found\n");
							sentinal= 1;
						
						}
						else{
							temp= temp->left;
							// if less go left
						}
					}
					
					if (hold > temp->data){
						if (temp->right==NULL){
							printf("No duplicates were found\n");
							sentinal= 1;	
						}
						else{
							temp= temp->right;
							// if greater go right
						}
					}
					

				}		
			}
		}
		if (hold==32){
			printf("ended search sequence.\n");
		}
		else{
			printf("%4s what character should we check for (searching for a space " " will end the search)\n%5s: ","","");
			hold= fgetc(stdin);
		}
	}
	if (sentinal_dup==1){
		printf("A duplicate of that character was found \n");
	}
	else{
		printf("No duplicates of that character were located\n");
	}
}

//------------------------------------------------------- get name func
void get_name(char **fileNamePtr){
	char name[200];
	char *distMarker;
	char *tempNamePtr;
	int a_counter=0;
	int b_counter=0;
	int checker=0;
	int dist=0;
	

	printf("\tWhat is the name (directory path) of the file to copy into a tree\n\t: ");
	
	
	fgets(name, 200,stdin);
	if ((distMarker = strchr(name, '\n'))==NULL)
		printf("\tThere was a problem determining the end of the name string\n");
	
	*distMarker='\0';
	dist= distMarker-name;
	
	if ((tempNamePtr = calloc(1, dist))==NULL)
		printf("\tThere was a problem locating a space for the name\n");
	
	while (a_counter< dist){
		tempNamePtr[a_counter]= name[a_counter];
		a_counter++;
	}
	
	
	while (b_counter<dist){
		if (tempNamePtr[b_counter]!= name[b_counter]){
			checker+=1;
		}
		b_counter++;
	}
	
	if(checker==0){
		(*fileNamePtr)= tempNamePtr;
	}
	else{
		(*fileNamePtr)= NULL;
	}
}
//------------------------------------------------------- preorder
void preorder(BranchPtr currNode){
	if (currNode!=NULL){
		printf("%c ",(*currNode).data);
		preorder(currNode->left);
		preorder(currNode->right);
	}
}

//------------------------------------------------------- inorder
void inorder(BranchPtr currNode){
	if (currNode!=NULL){
		inorder(currNode->left);
		printf("%c ",(*currNode).data);
		inorder(currNode->right);
	}
}

//------------------------------------------------------- postorder
void postorder(BranchPtr currNode){
	if (currNode!=NULL){
		postorder(currNode->left);
		postorder(currNode->right);
		printf("%c ",(*currNode).data);
	}
}

//------------------------------------------------------- freeTheTree
void freeTheTree(BranchPtr currNode){
	if (currNode!=NULL){
		postorder(currNode->left);
		postorder(currNode->right);
		free(currNode);
		currNode=NULL;
	}
	//modeled after postorder()
}

//------------------------------------------------------- insert
void insert(BranchPtr *rootPtr, char **fileName){
	BranchPtr temp= *rootPtr;
	FILE *filePtr;
	char hold;
	int sentinal=0;
	unsigned int copies= 0;
	
	if((filePtr= fopen(*fileName,"rb"))==NULL)
		printf("\tThere was a problem opening the file.\n");
	
	while ((hold= fgetc(filePtr))!=EOF){
		
		sentinal=0;
		temp=*rootPtr;
		
		while (sentinal==0){
			if (*rootPtr==NULL){
				if ((*rootPtr= calloc(1, sizeof(Branch)))!=NULL){
					(*rootPtr)->data= hold;
					(*rootPtr)->left=NULL;
					(*rootPtr)->right=NULL;
					sentinal=1;
				}
				else {
					printf("no more memory! (there was a problem allocating memory for the last node!)\n");
				}
			}
			else {
				while(sentinal==0){
					if (temp->data == hold){
						copies++;
						sentinal= 1;
						// if dup then disregard
					}
					
					if (hold < temp->data){
						if (temp->left==NULL){
							if ((temp->left= calloc(1, sizeof(Branch)))!=NULL){
								temp=temp->left;
								temp->data= hold;
								temp->left=NULL;
								temp->right=NULL;
							}
							else {
								printf("no more memory! (there was a problem allocating memory for the last node!)\n");
							}
							sentinal= 1;
							//if new value store in new branch
						}
						else{
							temp= temp->left;
							// if less go left
						}
					}
					
					if (hold > temp->data){
						if (temp->right==NULL){
							if ((temp->right= calloc(1, sizeof(Branch)))!=NULL){
								temp=temp->right;
								temp->data= hold;
								temp->left=NULL;
								temp->right=NULL;
							}
							else {
								printf("no more memory! (there was a problem allocating memory for the last node!)\n");
							}
							sentinal= 1;
							//if new value store in new branch
						}
						else{
							temp= temp->right;
							// if greater go right
						}
					}
					

				}		
			}
		}
		if (hold==32){
			printf("ended insertion stream.\n");
		}
	}
	printf("\nduplicates chopped from the tree: %d \n", copies);
	fclose(filePtr);
}

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
// printf("is this where the failure is?");