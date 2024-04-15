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
void copy_to_stack(char **fileName, Node **top);//open file- read que to file- close file //deqeue
int write_to_file(char ** fileName, Node **top);//print prioritized characters
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
	
	

	while (choice!=4){
			choice=0;
			choice =instructions();
		switch (choice){
			case 1:// copy file
				get_name(&fileName, choice);
				if ((fileName)==NULL){
					printf("\tThe operation was aborted due to unacceptable file name\n");
				}
				else{
				    printf("\tFilename handling complete\n");
					prioChar_count=0;
					prioChar_count= copy_to_qeue(&fileName, &head, &tail);//enqeues the contents of file and returns a value == num of prioritized characters
					
					if (head!=NULL){
					    printf("\tThe file contents were successfully distributed into a qeue\n");
					    printf("\n\tnumber of prioritized characters:  %d\n\n", prioChar_count);//print num of characters prioritized
					}
					
				}
				break;
			case 2:// copy file
				get_name(&fileName, choice);
				if ((fileName)==NULL){
					printf("\tThe operation was aborted due to unacceptable file name\n");
				}
				else{
				    printf("\tFilename handling complete\n");
					copy_to_stack(&fileName, &head);//distribute contents into the stack
					if (head!=NULL){
					    printf("\tThe file contents were successfully distributed into a stack\n");
					}
				}
				break;
			case 3:// paste file
				get_name(&fileName, choice);
				if ((fileName)==NULL){
					printf("\tThe operation was aborted due to unacceptable file name\n");
				}
				else{
					writChar_count = write_to_file(&fileName, &head);//open file- deqeue/pop off stack into file- print num of char written- close file 
					printf("\tThe number of characters written was: (%d)\n", writChar_count);//print num of characters written
				}
				
				break;
			default: //free memory // end program
				free(fileName);
				break;
		}
		
	}
	return 0;
}
//--------------------------------------------------------------instructions func
int instructions(){
	int choice;
	char trash[3];
	while (choice <1 || choice > 4){
		printf("\tProgram Functions:\n%15s (1) Copy file a file to a qeue \n%15s (2) copy a file to a stack \n%15s (3) Paste node sequence to a file \n%15s (4) End Program\nChoice:  ","","","","");
		scanf("%d", &choice);
		fgets(trash,2,stdin);
		if (choice <1 || choice > 4){
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
	
	if (choice!=3){
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
int copy_to_qeue(char **fileName, Node **head, struct qeueNode **tail){
	NodePtr newNode =NULL;
	NodePtr backOfPrio =NULL;
	FILE *filePtr;
	int prioCounter=0;
	char letter;
	int isVowel;
	int headCheck;
	int counter=0;
	char vowels[12]={'a','A','e','E','i','I','o','O','u','U','y','Y'}; //treating all y's as vowels
	
	if((filePtr= fopen(*fileName,"r"))==NULL)
		printf("\tThere was a problem opening the file.\n");
	
	while ((letter= fgetc(filePtr))!=EOF){
		isVowel=0;//reset vowel checker
		
		for (counter=0; counter<12 ;counter++){
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
				else{ 
					headCheck=0;
					
					for (counter=0; counter<12 ;counter++){//------check if 
						if ((*head)->value== vowels[counter])//----head value
						headCheck=1;//if vowel set to 1------------is a vowel
					}
					
					if (isVowel==0){
						(*newNode).next= (*head);
						(*head)= newNode;
					}
					else if (backOfPrio==NULL){
						backOfPrio=newNode;
						if ((*tail)==NULL){
							(*head)->next=backOfPrio;
							//(*tail)=backOfPrio;
						}
						else{
							backOfPrio->next=(*head)->next;
							(*head)->next= backOfPrio;
						}
					
					}
					else {
						(*newNode).next= (*backOfPrio).next;
						(*backOfPrio).next=newNode;
						backOfPrio= newNode;
					}
				}
			}
			else {
				if ((*head)==NULL){
					(*head)=newNode;
				}
				else if ((*tail)==NULL){
					if (backOfPrio==NULL){
						(*head)->next= newNode;
						(*tail)= newNode;
					}
					else {
						backOfPrio->next= newNode;
						(*tail)= newNode;
					}
				
				}
				else {
					(**tail).next= newNode;
					(*tail)= newNode;
				}
			}
		}
	}
	fclose(filePtr);
	filePtr=NULL;
	return prioCounter;
}

//--------------------------------------------------------------copy to stack
void copy_to_stack(char **fileName, Node **top){
    NodePtr newNode=NULL;
    FILE *filePtr=NULL;
    char letter;
		
		if((filePtr= fopen(*fileName,"r"))==NULL){
		printf("\tThere was a problem opening the file.\n");
		}
		else{
		    while ((letter= fgetc(filePtr))!=EOF){
		        if ((newNode= calloc(sizeof(Node), 1))==NULL){
		          printf("\tThere was a problem allocating space for a node.\n");
		        }
		        else{
		    	  (*newNode).value=letter;// storing Node's data
			      (*newNode).next= *top;//initializing tail end pointer to NULL
			      (*top)=newNode;//trailing the head Ptr along the additions of nodes
		        }
		    }
		}
		fclose(filePtr);
		filePtr=NULL;
}
//--------------------------------------------------------------copy list to file
int write_to_file(char ** fileName,  NodePtr *top){
	NodePtr prev=NULL;
	int writeChar=0;
	FILE *filePtr=NULL;
	
	
	if((filePtr= fopen(*fileName,"w"))==NULL){
		printf("\tThere was a problem opening the file.\n");
	}
	else{
		while (*top!=NULL){
			if ((fputc((**top).value, filePtr))!=((**top).value)){
				printf("\tThere was a write error in the (%d) character\n",writeChar+1);
			}
			else {
				writeChar++;
				prev = *top;
				(*top)= (**top).next;
				free(prev);
				prev=NULL;	
			}
		}
	}
	fclose(filePtr);
	filePtr=NULL;
	return writeChar;
}
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------