#include <stdio.h>
/*
NOTE TO SELF:
6 total subroutine functions, only difference should be name and integer call style as noted in the switchGet function, only make changes to the specified variable for control maintenance
*/

/*this program is supposed to reveal the inner workings and results of the various methods to pass values and pointers to a subroutine function. the initial values and addresses of the main function's 'value' integer and 'pointer' pointer are printed at the start of the main function (for reference), at the start of the selected subroutine function (twice-one more at the end of the subroutine- if any action is taken, within that subroutine, that may alter the value or address of the targeted parameter), and again at the end of the main function (to check if any of said actions altered the parameter of the main function's target argument).

hopefully this will track the behaviors of the variables and provide further insight into their workings

NOTE: the 'pointer' value and the 'value' address should always be the same, if they are not it means that the pointer is not pointing to the correct location. */

/*
NOTE TO SELF:
I'm unsure whether pointer values and address locations should be printed as characters or not, so I printed them as both characters and numbers--- fix this before submission.
*/

//------------------------------------------------------------------------------------------ pointer functions
//- - -- - -- - -- - -- - -- - -- - -- - -- - -- - - pointerPlain (int pointer)

int pointerPlain (int p, int x){
 int *pa;
 pa= &p; 
 if (x==0){
 printf("'pointer' value 	(d):	%d 		\\initial subroutine\n", p);
 printf("'pointer' value 	(c):	%c		\\initial subroutine\n", p);
 printf("'pointer' address	(d):	%d		\\initial subroutine\n", &p);
 printf("'pointer' address	(c):	%c		\\initial subroutine\n\n", &p);
 return p;
 }
 else
 return pa;
 }
//- - -- - -- - -- - -- - -- - -- - -- - -- - -- - - pointerStar (int *pointer)

int pointerStar (int *p, int x){
 int *pa;
 pa= &p; 
 if (x==0){
 printf("'pointer' value 	(d):	%d 		\\final subroutine\n", p);
 printf("'pointer' value 	(c):	%c		\\final subroutine\n", p);
 printf("'pointer' address	(d):	%d		\\final subroutine\n", &p);
 printf("'pointer' address	(c):	%c		\\final subroutine\n\n", &p);
 return p;
 }
 else
 return pa;
 }
//------------------------------------------------------------------------------------------ value  functions
//- - -- - -- - -- - -- - -- - -- - -- - -- - -- - - valuePlain (int value)

int valuePlain (int v, int x){
 int* va;
 va= &v;
 if (x==0){
 printf("'value' value       	(d):	%d		\\initial subroutine\n", v);
 printf("'value' address	(d):	%d		\\initial subroutine\n", &v);
 printf("'value' address	(c):	%c		\\initial subroutine\n\n", &v);

 v=v+1;

 printf("'value' value       	(d):	%d		\\final subroutine\n", v);
 printf("'value' address	(d):	%d		\\final subroutine\n", &v);
 printf("'value' address	(c):	%c		\\final subroutine\n\n", &v);
 return v;
 }
 else
 return va;
}
//- - -- - -- - -- - -- - -- - -- - -- - -- - -- - - valueStar (int *value)

int valueStar (int *v, int x){
 int *va;
 va= &v;
 if (x==0){
 printf("'value' value       	(d):	%d		\\initial subroutine\n", v);
 printf("'value' address	(d):	%d		\\initial subroutine\n", &v);
 printf("'value' address	(c):	%c		\\initial subroutine\n\n", &v);

 v=v+1;

 printf("'value' value       	(d):	%d		\\final subroutine\n", v);
 printf("'value' address	(d):	%d		\\final subroutine\n", &v);
 printf("'value' address	(c):	%c		\\final subroutine\n\n", &v);
 return v;
 }
 else
 return va;
}
//------------------------------------------------------------------------------------------ switchGet ()

int switchGet (){

 int swtc;
 printf("what would you like to test?\n\n");
 printf("		(1) pass pointer by value 			\\(int pointer)\n");
 printf("		(2) pass pointer by reference 		\\(int *pointer)\n\n");

 printf("		(3) pass variable by value 			\\(int value)\n");
 printf("		(4) pass variable by reference		\\(int *value)\n\n");
 printf("		(0) close program\n\n");
 printf("	   : ");
 
 scanf("%d", &swtc);
 return swtc;
}
//------------------------------------------------------------------------------------------ main

int main (){

 int value;
 int * pointer;
 int returnValue[2]= {-1, -1};
 int returnPointer[2]= {-1, -1};
 int switchNum= -1;
 int xMain;
 printf("this is the 'POINTER PASS / VALUE PASS' program\n\n");



while (switchNum!= 0){
 value= 27093;
 pointer= & value;
 xMain=0;
 // "x" is gonna be used to coordinate what gets used on the first and second runs through the subroutines
 printf("'pointer' value 	(d):	%d 		\\initial main\n", pointer);
 printf("'pointer' value 	(c):	%c		\\initial main\n", pointer);
 printf("'pointer' address	(d):	%d		\\initial main\n", &pointer);
 printf("'pointer' address	(c):	%c		\\initial main\n\n", &pointer);
 printf("'value' value       	(d):	%d		\\initial main\n", value);
 printf("'value' address	(d):	%d		\\initial main\n", &value);
 printf("'value' address	(c):	%c		\\initial main\n\n", &value);

 switchNum= switchGet();


 switch (switchNum){
  case 1: 
   while (xMain<2){
    returnPointer[xMain]=pointerPlain(pointer, xMain);
	xMain++;
  }
   break; 
  case 2:
   while (xMain<2){
    returnPointer[xMain]=pointerStar(pointer, xMain);
	xMain++;
    }
   break;
  case 3: 
   while (xMain<2){
	returnValue[xMain]=valuePlain(value,xMain);
	xMain++;
    }
   break;
  case 4:
   while (xMain<2){
	returnValue[xMain]=valueStar(value,xMain);
	xMain++;
	}
   break;
  case 0: return 0;
   break;
  else: printf("NOT VALID, TRY AGAIN:\n\n");
   break;
  }
  if (switchNum<5 && switchNum>0){
 printf("'pointer' value 	(d):	%d 		\\final main\n", pointer);
 printf("'pointer' value 	(c):	%c		\\final main\n", pointer);
 printf("'pointer' address	(d):	%d		\\final main\n", &pointer);
 printf("'pointer' address	(c):	%c		\\final main\n\n", &pointer);
 printf("'value' value		(d):	%d		\\final main\n", value);
 printf("'value' address	(d):	%d		\\final main\n", &value);
 printf("'value' address	(c):	%c		\\final main\n\n\n", &value);
  }
 }
 }