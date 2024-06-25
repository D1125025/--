#include<stdio.h>
#include<stdlib.h>
char stack[128] = {0};

int pop(int top){
    if(top > -1){
        top--;
    }
    return top;
}

int push(int top,char c){
    if(c == ']'){
        if(stack[top] == '['){
            top = pop(top);
        }
        else{
            top++;
        }
    }
    else if(c == ')'){
        if(stack[top] == '('){
            top = pop(top);
        }
        else{
            top++;
        }
    }
    else{
        top++;
        stack[top] = c;
    }
    // printf("%d\n",top);
    return top;
}

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        
        int top = -1;
        char arr[128] = {'\0'};
        int i =0;
    
        scanf("%s",arr);
        
        while(arr[i] != '\0'){
            top = push(top,arr[i]);
            // printf("!\n");
            i++;
        }
        if(top  == -1){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }

        // for(int i = 0;arr[i] !='\0' ;i++){
        //     printf("%c ",arr[i]);
        // }
        // printf("!\n");
    }
    return 0;
}