#include <stdio.h>

FILE *in;
FILE *out;

void fun(int x){

    if(x != 0){

        if(x % -2 == -1){
            fun(x/-2+1);
            fprintf(out,"1");
        }
        else{
            fun(x/-2);
            fprintf(out,"%d",x % -2);
        }
    }
}

int main(){

    in = fopen("input.txt","r+");
    out = fopen("output.txt","w+");
    int x;
    while(fscanf(in,"%d",&x)!= EOF){

        printf("%d\n",x);
        if(x == 0){
            fprintf(out,"0\n");
        }
        else{
            fun(x);
            fprintf(out,"\n");
        }
        
    }
    fclose(in);
    fclose(out);
}
