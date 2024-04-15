#include <stdio.h>
#include <ctype.h>

int main (){

	char c;
	
	printf("enter a number or letter.\n\n		:  ");
	scanf("%c", &c);
	printf("\n\n");

	while (c!='z' && c!='Z'){
		
		if (isalpha(c))
			printf("DING\n\n");
		if (isdigit(c))
			printf("DONG\n\n");

		
		printf("enter a number or letter.\n\n		:  ");
		scanf("\n%c", &c);
		printf("\n\n");
	}

	printf("The zed word!\n\n");
	
	return 0;
	
}