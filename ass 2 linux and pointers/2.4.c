include <stdio.h>

void passbyRef (int *val){
        int newNum;
        printf("gimme a new numbre:  ");
        scanf("%d", &newNum);
        *val= newNum;
}

void passbyValue (int val){
        int newNum;
        printf("gimme a new number:  ");
        scanf("%d", &newNum);
        val= newNum;
}

int main (){
        int num;
        int passbyNum;
        int *pointer;
        pointer= &num;
        printf("pick a number:  ");
        scanf("%d", &num);
        printf("your number is %d", num);


        printf("your choices are:\n");
        printf("        (1) pass by reference\n");
        printf("        (2) pass by value\n");
        printf("choose:  ");
        scanf("%d", &passbyNum);

        if (passbyNum==1){
                passbyRef(pointer);
                printf("\n");
                printf("passing by reference should overwrite your old number, making your chosen number also: %d\n", num);
        }
        else if (passbyNum==2){
                passbyValue(num);
                printf("\n");
                printf("passing by value should only affect a copy of your old number, meaning your chosen number, as known by the main function, is still %d\n", num);
        }

        return 0;
}
