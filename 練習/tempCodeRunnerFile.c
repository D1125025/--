#include <stdio.h>
int stack[10];
int top = -1;

int isFull(int top){
    if(top == 9){
        printf("FULL!!!\n");
        return 1;
    }
    return 0;
}

int isEmpty(int top){
    if(top == -1){
        printf("EMPTY!!!\n");
        return 1;
    }
    return 0;
}

void push(int *top,int num){
    if(!isFull(*top)){
        (*top)++;
        stack[*top] = num;
    }
}

void pop(int *top){
    if(!isEmpty(*top)){
        (*top)--;
        printf("%d\n",stack[*top+1]);
    }
}

void popAll(int *top){
    while(*top != -1){
        pop(top);
    }
}

int main(){
    
    push(&top,1);
    push(&top,2);
    push(&top,3);
    pop(&top);
    push(&top,4);
    push(&top,5);
    push(&top,6);
    push(&top,7);
    push(&top,8);
    push(&top,9);
    push(&top,10);
    popAll(&top);
}