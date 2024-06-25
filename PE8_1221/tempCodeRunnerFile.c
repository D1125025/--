#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listnode{
    int delay;
    struct listnode *left;
    struct listnode *right;
}treenode;

treenode* create_node(int value){

    treenode *newnode = (treenode*)malloc(sizeof(treenode));
    newnode->delay = value;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

treenode* inorder(int in[],int post[],int instart,int inend,int poststart,int postend){

    if(instart > inend || poststart > postend){
        return NULL;
    }

    int rootvalue = post[postend];
    treenode* root = create_node(rootvalue);

    int i;
    for(i = instart;i < inend;i++){
        if(in[i] == rootvalue){
            break;
        }
    }

    int letfnum = i - instart;
    root->left = inorder(in,post,instart,i-1,poststart,poststart+letfnum-1);
    root->right = inorder(in,post,i+1,inend,poststart+letfnum,postend-1);

    return root;
}

void skew(treenode *root,int *longest,int *shortest,int currentdelay){

    if(root == NULL){
        return;
    }
    currentdelay += root->delay;

    if (root->left == NULL && root->right == NULL) {
        
        if (currentdelay > *longest) {
            *longest = currentdelay;
        }
        if (currentdelay < *shortest) {
            *shortest = currentdelay;
        }
        return;
    }

    // 遞迴處理左子樹和右子樹
    skew(root->left, longest, shortest, currentdelay);
    skew(root->right, longest, shortest, currentdelay);

}

int main(){
    char buffer[1024];
    int num,a,b,i = 0,j = 0;
    int in[100],post[100];

   fgets(buffer, sizeof(buffer), stdin);
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        in[i++] = atoi(token);
        token = strtok(NULL, " ");
    }


    fgets(buffer, sizeof(buffer), stdin);
    token = strtok(buffer, " ");
    while (token != NULL) {
        post[j++] = atoi(token);
        token = strtok(NULL, " ");
    }

    treenode* root = inorder(in,post,0,i,0,j);

    int longest = 0;
    int shortest = 10000;

    // 計算最長和最短路徑
    skew(root, &longest, &shortest, 0);

    // 輸出結果
    printf("Delayed time (longest path) = %d\n", longest);
    printf("Delayed time (shortest path) = %d\n", shortest);

}
