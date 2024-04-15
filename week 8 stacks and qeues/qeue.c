//--------------------------------------------------------------preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct qeueNode{
	char value;
	struct qeueNode *next;
	} Node;
typedef Node *NodePtr;

//--------------------------------------------------------------prototypes
int instructions();//instructions
void get_name(char **fileNamePtr, int choice);//get file name
int copy_to_qeue(char **fileName, Node **head, Node **tail);//open file- read file to que- close file //enqeue (proritize vowels to the front of the qeue)
//open file- read que to file- close file //deqeue
//print prioritized characters
//print characters written
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------main func
int main(){
	char *fileName;
	int writChar_count;
	int prioChar_count;
	int choice=0;
	NodePtr head=NULL;
	NodePtr tail=NULL;
	
	

	while (choice!=3){
			choice =instructions();
		switch (choice){
			case 1:// copy file
				get_name(&fileName, choice);
				if ((fileName)==NULL){
					printf("\tThe operation was aborted\n");
				}
				else{
				    printf("\tFilename handling complete\n");
					prioChar_count=0;
					prioChar_count= copy_to_qeue(&fileName, &head, &tail);
					if (head!=NULL){
					    printf("\tThe file contents were successfully distributed into a qeue\n");
					    printf("\tnumber of prioritized characters:  %d\n\n", prioChar_count);
					}
					//open file, read char by char into qeue
					
				}
				//print num of characters prioritized
				break;
			case 2:// paste file
				get_name(&fileName, choice);
				if ((fileName)==NULL){
					printf("\tThe operation was aborted\n");
				}
				else{
					//open file deqeue into file close file
				}
				//print num of characters written
				
				break;
			default: //free memory // end program
				break;
		}
		
	}
	return 0;
}
/*





note space:
free:
	nodes:
		should be freed during the deqeue
	main:
		char *fileName
		
	


*/
//--------------------------------------------------------------instructions func
int instructions(){
	int choice;
	char trash[3];
	while (choice <1 || choice > 3){
		printf("\tProgram Functions:\n%15s (1) Copy File \n%15s (2) Paste File \n%15s (3) End Program\nChoice:  ","","","");
		scanf("%d", &choice);
		fgets(trash,2,stdin);
		if (choice <1 || choice > 3){
			printf("\n\n\tINVALID SELECTION\n\n");
		}
	}
	return choice;
}
//-------------------------------------------------------------- get name func
void get_name(char **fileNamePtr, int choice){
	char name[200];
	char *distMarker;
	char *tempNamePtr;
	int a_counter=0;
	int b_counter=0;
	int checker=0;
	int dist=0;
	
	if (choice=1){
		printf("\tWhat is the name (directory path) of the file to copy\n\t: ");
	}
	else {
		printf("\tWhat is the name (directory path) of the file to paste\n\t: ");
	}
	
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
//-------------------------------------------------------------- copy to qeue func
int copy_to_qeue(char **fileName, Node **head, Node **tail){
	NodePtr newNode =NULL;
	NodePtr backOfPrio =NULL;
	FILE *filePtr;
	int prioCounter=0;
	char letter;
	int isVowel;
	int counter=0;
	char vowels[6]={'a','e','i','o','u','y'}; //treating all y's as vowels
	
	if((filePtr= fopen(*fileName,"rb"))==NULL)
		printf("\tThere was a problem opening the file.\n");
	
	while ((letter= fgetc(filePtr))!=EOF){
		isVowel=0;//reset vowel checker
		
		for (counter=0; counter<6 ;counter++){
			if (letter== vowels[counter]){
				isVowel=1;//if vowel set to 1
				prioCounter+=1;//incrememnt prioritization counter
			}
		}
		
		if ((newNode= calloc(sizeof(Node), 1))==NULL){
			printf("\tThere was a problem allocating space for a node.\n");
		}
		else{
			(*newNode).value=letter;// storing Node's data
			(*newNode).next=NULL;//initializing tail end pointer to NULL
			
			if (isVowel==1){
				if ((NodePtr)(*head) ==NULL){
					(*head)=newNode;
				}
				else if (backOfPrio==NULL){
					if ((*tail)==NULL){
						backOfPrio=newNode;
						(*head)->next=backOfPrio;
						(*tail)=backOfPrio;
					}
					else{
						backOfPrio= newNode;
						(*head)->next= backOfPrio;
					}
					
				}
				else {
					(*newNode).next= (*backOfPrio).next;
					backOfPrio= newNode;
				}
			}
			else {
				if ((*head)==NULL){
					(*head)=newNode;
				}
				else if ((*tail)==NULL){
					(*head)->next= newNode;
					(*tail)= newNode;
				}
				else {
					(**tail).next= newNode;
					(*tail)= newNode;
				}
			}
		}
	}
	fclose(filePtr);
	return prioCounter;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
