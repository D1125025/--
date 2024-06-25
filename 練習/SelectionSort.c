#include <stdio.h>

int main(){

    int size;
    scanf("%d",&size);
    
    int num[size];
    for(int i = 0;i <size;i++)
        scanf("%d",&num[i]);
    
    // for(int i = 0;i < size;i++)
    //     printf("%d",num[i]);

    for(int i = 1;i < size;i++){
        int min;
        for(int j = i+1;j < size;j++){
            

            if(num[i] < num[j])
                min = i;
            else
                min = j;
            
        }
        if(num[i-1] > num[min]){
            int tmp = num[i-1];
            num[i-1] = num[min];
            num[min] = tmp;
        }

    }
    for(int i = 0;i < size;i++)
        printf("%d ",num[i]);
}