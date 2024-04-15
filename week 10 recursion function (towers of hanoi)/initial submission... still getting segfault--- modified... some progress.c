//---------------------------------------------preprocessor
#include <stdio.h>
#include <stddef.h>

typedef struct disk{
		/*
	node feature:
	-	a number corresponding to number of disks on a peg (bottom disk being 1, second being 2... up to the top disk)
		mod (%2) that number to determine if even or odd stack behavior (0= even, 1= odd)*/
	unsigned int count;
	unsigned int size;
	struct disk *next;
	} Disk;

typedef Disk *Diskptr;

	
//---------------------------------------------prototypes
void buildGame(unsigned int counter, Diskptr **pegPtr);// assign designated # of nodes to stack a
unsigned long int  movestack(unsigned int DiskNumber, Diskptr **pegPtr, unsigned long int pegCycle);//(diskNumber, dest, source, spare) 



//---------------------------------------------main 
int main(){
	unsigned int diskNum;
	unsigned long int moves;
	Diskptr peg[3]={NULL,NULL,NULL};
	
	printf("how many disks would you like to play with: \n");
	scanf("%u", &diskNum);
	
	buildGame(diskNum, &peg);
	
	printf("processing\n");
	moves= movestack(diskNum, &peg, 0);
	printf("%lu \n", moves);
	
	
	return 0;
}

//---------------------------------------------move stack
unsigned long int movestack(unsigned int DiskNumber, Diskptr **pegPtr, unsigned long int pegCycle){
	Diskptr hold;
	Diskptr *peg= *pegPtr;
	unsigned long int thisMove=0;
	unsigned long int otherMoves=0;
	int pegKey= pegCycle%3; //pegcycle is the number which tracks the current peg... each change of peg (coninuation of the cycle) adds 1 to the cycle- cycle%3 == current peg (hence the name pegKey)
	
//--------------------------------------------------------------------------------------------------- move disk

	if (((peg[pegKey])->count)%2==0){// stack has even number of disks	
		if (pegKey==0){
			if (((peg[pegKey]->size)<(peg[1]->size)) || peg[1]==NULL){ //move to peg_B
			
				hold= peg[pegKey];
				peg[pegKey]= (peg[pegKey])->next;
				if (peg[1]==NULL){
					hold->count=1;
				}
				else {
					hold->count= (peg[1]->count)+1;
				}
				hold->next= peg[1];
				peg[1]= hold;
				thisMove=1;
			}
			else{
				pegCycle++;
				thisMove=0;
			}
		}
		else{
			if (((peg[pegKey]->size)<(peg[0]->size)) || peg[0]==NULL){ //move to peg_A
				
				hold= peg[pegKey];
				peg[pegKey]= (peg[pegKey])->next;
				if (peg[0]==NULL){
					hold->count=1;
				}
				else {
					hold->count= (peg[0]->count)+1;
				}
				hold->next= peg[0];
				peg[0]= hold;
				thisMove=1;
			}
			else {
				pegCycle++;
				thisMove=0;
			}
		}
	}
/*		else {// stack has odd number of disks
			if (pegKey==2){
				if (((peg[pegKey]->size)<(peg[1]->size)) || peg[1]==NULL){ //move to peg_B
					
					hold= peg[pegKey];
					peg[pegKey]= (peg[pegKey])->next;
					if (peg[1]==NULL){
						hold->count=1;
					}	
					else {
						hold->count= (peg[1]->count)+1;
					}
					hold->next= peg[1];
					peg[1]= hold;
					thisMove=1;
				}
				else{
					pegCycle++;
					thisMove=0;
				}
			}
			else {
				if (((peg[pegKey]->size)<(peg[2]->size)) || peg[2]==NULL){ //move to peg_C
					
					hold= peg[pegKey];
					peg[pegKey]= (peg[pegKey])->next;
					if (peg[2]==NULL){
						hold->count=1;
					}
					else {
						hold->count= (peg[2]->count)+1;
					}
					hold->next= peg[2];
					peg[2]= hold;
					thisMove=1;
				}
				else {
					pegCycle++;
					thisMove=0;
				}
			}
		}
*/
//--------------------------------------------------------------------------------------------------- determine if to call again
/*	if ((peg[2]->count)!=DiskNumber) {
		otherMoves= movestack(DiskNumber, peg, pegCycle);
	}
	else {
		otherMoves=0;
	}*/
//--------------------------------------------------------------------------------------------------- return
	return ((unsigned long int)(thisMove+otherMoves));	
}
	
	
	


//---------------------------------------------build game
void buildGame(unsigned int counter,Diskptr *peg){
	Diskptr *peg= *pegPtr;
	unsigned int total= counter;
	Diskptr current=NULL;
	while (counter>0){
		if (peg[0]==NULL){
			peg[0]= calloc(1,sizeof(Disk));
			current= peg[0];
		}
		else{
			current->next= calloc(1,sizeof(Disk));
			current= current->next;
		}
		current->size= total-counter;
		current->count= counter;
	
		counter-=1;
	}
	
	
	return;
}
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------