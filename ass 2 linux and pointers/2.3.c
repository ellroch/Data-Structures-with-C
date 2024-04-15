#include <stdio.h>

void passbyRef (int *val){
	printf("new number:  ");
	scanf("%d", &val);
	
	printf("new number is:  %d", val);
}

void passbyValue (int val){
	printf("new number:  ");
	scanf("%d", &val);
	
	printf("new number is :  %d", val);
}

int main (){
	int num;
	int *pointer;
	pointer= &num;
	int passbyNum;
	
	printf("pick a number:  ");
	scanf("%d", &num);
	printf("your number is %d", num);
	
	
	printf("your choices are:\n");
	printf("	(1) pass by reference\n");
	printf("	(2) pass by value\n");
	printf("choose:  ");
	scanf("%d", &passbyNum);
	
	if (passbyNum==1){
		passbyRef( &num);
		printf("passing by reference should overwrite your old number, making your old number also: %d", num);
	}
	if (passbyNum==2){
		passbyValue(num);
		printf("passing by value should only affect a copy of your old number, meaning your old number is still: %d", num);
	}
return 0;
}