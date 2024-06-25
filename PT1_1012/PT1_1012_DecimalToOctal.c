#include <stdio.h>

void fun(int x){

    if(x!=0){
        // if(x % 8 == 0){
        //     fun(x/8);
        //     printf("0");
        // }
        if(x % 8 != 0){
            fun(x/8);
            printf("%d",x%8);
        }
        else{
            fun(x/8);
            printf("%d",x%8);
        }
    }
}
int main(){
    
    int round = 1,x,num;
    scanf("%d",&x);

    while(x--){
        
        scanf("%d",&num);
        printf("Case #""%d"":",round);
        if(num ==0)
            printf("0\n");
        else{
            fun(num);
            printf("\n");
        } 
        round++;
    }
}