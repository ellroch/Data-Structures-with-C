#include <stdio.h>
#include <stdlib.h>

int main(){
	//-----variables
	int size;
	int counter;
	int *dynArray;
	int *tempPtr;
	// get size of dynaimc array
	printf("\t%-30s:\t", "how many numbers:");
	scanf("%d", &size);
	printf("\n");
	// set memory for the array to = int size*sizeof(int)
	dynArray= malloc(size*sizeof(int));
	if (dynArray== NULL)
		printf("dynArray NULL value");
	// read in loop
	for (counter=0; counter<size; counter++){
		tempPtr= (dynArray+(counter*sizeof(int)));
		printf("\t%-2d) %-26s:\t", counter+1, "number");
		scanf("%d", tempPtr);
	}
	// 
	printf("\n");
	// print out loop
	for (counter=0; counter<size; counter++){
		tempPtr=(dynArray+(counter*sizeof(int)));
		printf("\t%-2d) %26s:\t%d\n", counter+1, "", *tempPtr);
	}
	
	
	free(dynArray);
return 0;
}