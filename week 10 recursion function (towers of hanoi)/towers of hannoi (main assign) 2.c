// I feel like my recursive function passes a lot of information each call... but It came most naturally... I assume there is something with less passing involved and im curious what it is.
#include <stdio.h>

#define peg[0] peg_A
#define peg[1] peg_B
#define peg[2] peg_C

typedef struct disk{
		/*
	node feature:
	-	a number corresponding to number of disks on a peg (bottom disk being 1, second being 2... up to the top disk)
		mod (%2) that number to determine if even or odd stack behavior (0= even, 1= odd)*/
	unsigned int stack_count;
	unsigned int size;
	struct disk *next;
	} Disk;

typedef Disk *diskPtr;
	
//---------------------------------------------prototypes
void buildGame();// assign designated # of nodes to stack a
void movestack();//(diskNumber, dest, source, spare) 



//---------------------------------------------main 
int main(){
	diskPtr peg[3];
	return 0;
}

//---------------------------------------------move stack
void movestack(){
	// source feature can be an array of void pointers (they are in sequence then) so u can pass the start of the pointer and a tracker (of %3(for a-b-c)). when one peg is complete add one to tracker and pass tracker along with array to access the element
	/*
	special conditions:
	-	cant move same disk 2x in a row
	-	move all possible disks on one peg before moving to the next... cycle pegs abc-abc-abc...
	*/
	
	/* struggled with how to determine the destination for a while, noticed a pattern by looking at this image: (it's 'interactive' so u have to push the little plus at the bottom to see the full thing)
	https://upload.wikimedia.org/wikipedia/commons/2/20/Tower_of_Hanoi_recursion_SMIL.svg
	the wiki page on hanoi tower noted something about starting on different pegs depending if it's odd or even. I wrote a little diagram holding each peg (source) for odd and even # of disks and wrote the corresponding movement.
	odd:
	a -> c
	b -> c
	c -> b
	even:
	a -> b
	b -> a
	c -> a
	... I found these to be constant for the 4 disk puzzle and I assume it continues to be for each puzzle of greater scale, so I modeled my code after it... 
		- I'm unsure about whether looking at the chart dodged some of the work... I get the feeling that there might have been some concept that I forwent... frankly im wondering, did i cheat by using the chart- or was it ok?
		-Also, in the lesson's pseudo-code I didnt understand the 'spare' or the  'diskNumber-1' variables--- and they are shuffled around in each call... were they just there for examples? or was there meaning behind them
		(or the plain disknumber --- i assume it was what im using as size but then i dont understand the -1 so it confused me)
	
	*/
/*

if (disk ==0){
		if (stack has even number of disks){
			if (source is peg_A){
				move to peg_B
			}
			else{
				move to peg_A
			}
		}
		else {
			// stack has odd number of disks
			if (source is peg_C){
				move to peg_B
			}
			else {
				move to peg C
			}
		}
}
else {
	movetower(diskNumber-1,source,spare,dest) // recursive call (the parameters are from the provided pseudocode)
	move disk from source to dest.
	movetower(diskNumber-1, pare,dest,source) // recursive call (the parameters are from the provided pseudocode)
}

*/
/*



*/
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
//---------------------------------------------