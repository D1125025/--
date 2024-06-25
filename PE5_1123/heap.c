#include<stdio.h>
int arr[1000] = {0};

void insert(int i){
    if(i == 0){
        return;
    }
    if(arr[i] < arr[(i-1)/2]){
        int tmp = arr[i];
        arr[i] = arr[(i-1)/2];
        arr[(i-1)/2] = tmp;
        insert((i-1)/2);
    }
}

void resort(int i){
    int minChild;
    if(arr[1] < arr[2]){

        minChild = 1;
    }
    else{
        minChild = 2;
    }
    int k = 0;
    while(arr[k] < arr[minChild] && k < i){
        int tmp = arr[k];
        arr[k] = arr[minChild];
        arr[minChild] = tmp;
        k = minChild;
        if(arr[k*2] < arr[k*2+1]){

            minChild = k*2;
        }
        else{
            minChild = k*2+1;
        }
    }
}

void delete(int max){
    int tmp = arr[0];
    arr[0] = arr[max -1];
    arr[max-1] = tmp;
    resort(max-1);
}


int main(){
    FILE* input;
    FILE* output;
    input = fopen("input.txt","r+");
    output = fopen("output.txt","w+");
    int n;
    while(fscanf(input,"%d",&n)!=EOF){
        int total = 0,plusnum = 0,min = 0;
        for(int i = 0;i <= n;i++){
            arr[i] = 0;
        }
        for(int i = 0;i < n;i++){
            fscanf(input," %d",&arr[i]);
            insert(i);
        }
        
        while(n >= 0){
            if(arr[1] > arr[2]){
                min = arr[2];
            }
            else{
                min = arr[1];
            }
            plusnum = arr[0] + min;
            total = total + plusnum;
            // printf("%d %d %d\n", arr[0], min, plusnum);
            delete(n);
            for(int i = 0;i < n-1;i++){
                printf("%d ",arr[i]);
            }
            delete(n);
            n = n - 2;
            arr[n] = plusnum;
            insert(n-2);
            
        }
        
        
        // for(int i = 0;i < n;i++){
        //     printf("%d ",arr[i]);
        // }
        // printf("%d",total);
        // printf("\n");
    }
}