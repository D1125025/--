#include <stdio.h>

int fun(int x){
    if (x!=0){
        if(x%-2==-1){
                fun(x/-2+1);
                printf("1");
         }
         else{
                fun(x/-2);
                printf("%d",x%(-2));
         }
    }
}

int main() {
    int a,t;
    scanf("%d",&t);
    while (t--){
        scanf("%d",&a);
        fun(a);
        printf("\n");
    }
}

// - 1 = 11       
// - 2 = 10       
// - 3 = 1101    
// - 4 = 1100     
// - 5 = 1111     
// - 6 = 1110     
// - 7 = 1001     
// - 8 = 1000     
// - 9 = 1011     
// -10 = 1010     