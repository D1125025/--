// #include <stdio.h>
// #include <stdlib.h>

// typedef struct tree *listptr;
// typedef struct tree{
//     int num;
//     listptr left;
//     listptr right;
// }tree;

// void insert(listptr head,int value){
//     if(head == NULL){
//         listptr tmp = malloc(sizeof(listptr));
//         tmp->left = NULL;
//         tmp->right = NULL;
//         tmp->num = value;
//         head = tmp;
//         free(tmp);
//     }
//     else if(value < head->num){
//         printf("2");
//         insert(head->left,value);
//     }
//     else if(value > head->num){
//         printf("3");
//         insert(head->right,value);
//     }
    
// }

// void printnode(listptr head){
//     while(head != NULL){
//         printf("%d ",head->num);
//         printnode(head->left);
//         printnode(head->right);
//     }
// }

// int main(){
//     listptr* head = NULL;
//     int num;

//     while(scanf("%d",&num) != EOF){
//         printf("%d\n",&head);
//         insert(head,num);
//         printnode(head);
//     }
// }

#include <stdio.h>
#include <stdlib.h>

typedef struct tree *listptr;
typedef struct tree {
    int num;
    listptr left;
    listptr right;
}tree;

void insert(listptr *head, int value) {
    if (*head == NULL) {
    
        listptr tmp = malloc(sizeof(tree));
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->num = value;

        *head = tmp;
    } else if (value < (*head)->num) {
        // printf("2");
        
        insert(&((*head)->left), value);
    } else if (value > (*head)->num) {
        // printf("3");
        
        insert(&((*head)->right), value);
    }
}

void printnode(listptr head) {
    if (head != NULL) {
        printnode(head->left);
        printf("%d ", head->num);
        printnode(head->right);
    }
}

int main() {
    listptr head = NULL;  // 使用 listptr 而不是 listptr* 因為listptr 已經是指針
    int num;

    while (scanf("%d", &num) != EOF) {
        // printf("%p\n", (void *)&head);  // 打印 head 指?的地址
        insert(&head, num);
        printnode(head);
    }

    return 0;
}
