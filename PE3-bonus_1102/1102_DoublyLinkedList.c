#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
    struct node *pre;
}node;

int main(){
    FILE * input = fopen("input.txt","r+");
    FILE * output = fopen("output.txt","w+");
    // char arr[5][100] = {"\0"};
    char i;
    node *firstnode = NULL,*lastnode = NULL;
    
    while(fscanf(input,"%c ",&i)!= EOF){
        int numB,numE;
        if(i == 'B'){
            fscanf(input,"%d ",&numB);
            // open ptrB to pretend it is the first one 
            node *ptrB = (node*) malloc (sizeof(node));
            ptrB->data = numB;
            ptrB->pre = NULL;
            ptrB->next = firstnode;
            // if firstnode have something inside 
            // we need to connect it BEHIND the new added ptrB
            if(firstnode != NULL){
                firstnode->pre = ptrB;
            }
            // move firstnode to the ptrB 
            firstnode = ptrB;
            // check lastnode is null or not 
            // if it is null it will be the firstnode
            if(lastnode == NULL){
                lastnode = firstnode;
            }
        }
        else if(i == 'E'){
            fscanf(input,"%d ",&numE);
            // open ptrE to pretend it is the last one 
            node *ptrE = (node*) malloc (sizeof(node));
            ptrE->data = numE;
            ptrE->pre = lastnode;
            ptrE->next = NULL;
            // if lastnode have something inside 
            // we need to connect it IN FRONT OF the new added ptrE
            if(lastnode != NULL){
                lastnode->next = ptrE;
            }
             // move lastnode to the ptrE
            lastnode = ptrE;
            // check firstnode is null or not 
            // if it is null it will be the lastnode
            if(firstnode == NULL){
                firstnode = lastnode;
            }
        }
        else if(i == 'R'){
            node *ptrR1 = (node*) malloc (sizeof(node));
            node *ptrR2 = (node*) malloc (sizeof(node));
            // if firstnode isn't null  delete it
            // so firstnode move to the next one
            if(firstnode != NULL){
                ptrR1 = firstnode->next;
                firstnode = ptrR1;
            }
            // if lastnode isn't null  delete it
            // so lastnode move to the previous one
            if(lastnode != NULL){
                ptrR2 = lastnode->pre;
                lastnode = ptrR2;
            }
        }
    }

    while(firstnode->next != NULL){
        fprintf(output,"%d->",firstnode->data);
        firstnode = firstnode->next;
    }
    fprintf(output,"%d->NULL\n",firstnode->data);

    while(lastnode->pre != NULL){
        fprintf(output,"%d->",lastnode->data);
        lastnode = lastnode->pre;
    }
    fprintf(output,"%d->NULL\n",lastnode->data);

    fclose(input);
    fclose(output);
}