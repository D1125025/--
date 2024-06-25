#include<stdio.h>
#include<stdlib.h>

typedef struct tree *list_ptr;
typedef struct tree{
    int value;
    list_ptr left;
    list_ptr right;
}tree;

void insert(list_ptr* head,int num){

    if(*head == NULL){
        list_ptr tmp = malloc(sizeof(tree));
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->value = num;
        *head = tmp;
        free(tmp);
    }
    else if(num < (*head)->value){

        insert(&(*head)->left,num);
    }
    else if(num > (*head)->value){

        insert(&(*head)->right,num);
    }
}

void printinorder(list_ptr head){

    if(head != NULL){

        printinorder(head->left);
        printf("%d ",head->value);
        printinorder(head->right);

    }
}

list_ptr findmin(list_ptr head){

    while(head->left != NULL){

        head = head->left;
    }
    return head;
}

list_ptr delete(list_ptr head,int num){

    if(num < head->value){
        head->left = delete(&head->left,num);
    }
    else if(num > head->value){
        delete(&head->right,num);
    }
    else{
        if(head->left == NULL){
            list_ptr tmp = head->right;
            head = tmp;
            free(tmp);
        }
        else if(head->right == NULL){

            list_ptr tmp = head->left;
            head = tmp;
            free(tmp);
        }
        else{

            head = findmin(&head);


        }
    }
}

int main(){
    list_ptr head = NULL;
    int num;
    while(scanf("%d",&num) != EOF){
        insert(&head,num);
        printinorder(head);
        
    }

    delete(&head,dnum);
}