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
    listptr head = NULL;  // �ϥ� listptr �Ӥ��O listptr* �]��listptr �w�g�O���w
    int num;

    while (scanf("%d", &num) != EOF) {
        // printf("%p\n", (void *)&head);  // ���L head ��?���a�}
        insert(&head, num);
        printnode(head);
    }

    return 0;
}
