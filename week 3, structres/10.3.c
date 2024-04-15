
# include <stdio.h>
# include <string.h>


struct part {
        unsigned partNumber;
        char partArray[25];
};

typedef struct part Part;

int main (){
        Part a;
        Part b[10];
        Part *ptr;
		char trash[25];
		int counter;

        printf("  2 digit partNumber for Part a:\n\n                         number:  ");
        scanf("%d", &a.partNumber);

		fgets(trash, 25, stdin);
		printf("\n\n");
		
        printf("  partName for part a:\n\n,                 name:  ");
        fgets(a.partArray, 25, stdin);

        (b[3]).partNumber = a.partNumber;
        for(counter=0;counter<25; counter++){
			
			(b[3]).partArray[counter]= a.partArray[counter];
			}

		
        ptr= &b[3];

        printf("number:  %d\n\n", ptr->partNumber);
        printf("name:   %s \n\n", (*ptr).partArray);


    return 0;
}
