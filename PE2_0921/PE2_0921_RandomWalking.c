#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc,char *argv[]){
    
    int n = atoi(argv[1]),m = atoi(argv[2]),ibug = atoi(argv[3]),jbug = atoi(argv[4]);
    if(n <= 2 || n > 40 || m <= 2 || m > 20 || ibug > n || jbug > m){          
        printf("error\n");
        return 0;
    }

    int total = 0;
    int count_arr[41][21] = {0};
    int run = 50000;
    int imove[8] = {-1,0,1,1,1,0,-1,-1};
    int jmove[8] = {1,1,1,0,-1,-1,-1,0};

    count_arr[ibug][jbug] = 1;

    srand(time(NULL));
    while(run--){
        
        int a = (rand() % 8);
        //check the bug is out of  wall or not
        while(ibug + imove[a] < 0 || ibug + imove[a] > 40 || jbug + jmove[a] < 0 || jbug + jmove[a] > 20)
            a = (rand() % 8);
        
        ibug = ibug + imove[a];
        jbug = jbug + jmove[a];
        
        count_arr[ibug][jbug]++;

        //check every block at least walk one time
        int flag = 0;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(count_arr[i][j] == 0)
                    flag = 1;
            }
        }
        
        if(flag == 0)
            break;
    }

    // count the total step
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++)
            total = total + count_arr[i][j];
    }
    
    FILE *output;
    output = fopen("output.csv","w+");
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            
            if(j == 0)
                fprintf(output,"%d",count_arr[i][j]);
            else
                fprintf(output,",%d",count_arr[i][j]);
            
        }
        fprintf(output,"\n");
    }
    fprintf(output,"%d",total);
    fclose(output);
}
