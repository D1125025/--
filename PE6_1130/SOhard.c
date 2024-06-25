#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int searchtime = 0;
int searchfailtime = 0;
int buytime = 0;
int buyfailtime = 0;
int insertime = 0;

typedef struct seller_data {
    char SID[30];
    int price;
} seller_data;

typedef struct Item *item_ptr;
typedef struct Item {
    char item_name[30];
    struct seller_data seller_heap[8];
    int seller_count;
    item_ptr leftchild;
    item_ptr rightchild;
} Item;

// compare two strings (every letter)
int cmp_(const char* str1, const char* str2) {
    while (*str1 && tolower((unsigned char)*str1) == tolower((unsigned char)*str2)) {
        ++str1;
        ++str2;
    }
    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

//insert 
item_ptr insert(item_ptr root, const char* itemName, const char* sellerName, int item_price) {
    printf("aaa\n");
    //if tree is empty
    if (root == NULL) {

        // create newnode to save new item
        item_ptr newnode = (item_ptr)malloc(sizeof(Item));
        newnode->leftchild = NULL;
        newnode->rightchild = NULL;
        strcpy(newnode->item_name, itemName);
        strcpy(newnode->seller_heap[0].SID, sellerName);
        newnode->seller_heap[0].price = item_price;
        newnode->seller_count++;

        return newnode;
    }
    else if (cmp_(itemName, root->item_name) < 0) {
        root->leftchild = insert(root->leftchild, itemName, sellerName, item_price);
    }
    else if (cmp_(itemName, root->item_name) > 0) {
        root->rightchild = insert(root->rightchild, itemName, sellerName, item_price);
    }
    else {
        strcpy(root->seller_heap[root->seller_count].SID, sellerName);
        root->seller_heap[root->seller_count].price = item_price;
        root->seller_count++;
    }

    int i = root->seller_count - 1;
    while(i != 0 && root->seller_heap[(i-1) / 2].price > root->seller_heap[i].price){
        // �洫���`�I�M��e�`�I
        seller_data tmp = root->seller_heap[i];
        root->seller_heap[i] = root->seller_heap[(i-1) / 2];
        root->seller_heap[(i-1) / 2] = tmp;
        i = (i-1) / 2;
    }
    return root;
}

void search(item_ptr root,const char* searchItemName,FILE* searchTable){
    if(root == NULL){
        searchfailtime++;
        fprintf(searchTable,"%s doesn't exist!\n",searchItemName);
        return;
    }
    else if(cmp_(searchItemName,root->item_name) == 0){
        fprintf(searchTable,"%s\n",root->item_name);
        for(int i = 0;i < root->seller_count;i++){
            fprintf(searchTable,"%s %d\n",root->seller_heap[i].SID,root->seller_heap[i].price);
        }
        fprintf(searchTable,"------------------------------\n");
    }
    else if(cmp_(searchItemName,root->item_name) < 0){
        search(root->leftchild,searchItemName,searchTable);
    }
    else{
        search(root->rightchild,searchItemName,searchTable);
    }
}


void minHeap(seller_data *arr, int n, int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left].price < arr[smallest].price){
        smallest = left;
    }
    if(right < n && arr[right].price < arr[smallest].price){
        smallest = right;
    }
    if(smallest != i){
        // �洫���`�I�M�̤p���l�`�I
        seller_data tmp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = tmp;

        // ���k�վ�Q�v�T���l��
        minHeap(arr,n,smallest);
    }
}

void deleteseller(seller_data *arr,int *n){//�R���@�ӽ�a
    if(*n <= 0){//�Y�S����[�F
        return;
    }

    // �N�ڸ`�I�P�̫�@�Ӹ`�I�洫
    seller_data temp = arr[0];
    arr[0] = arr[*n-1];
    arr[*n-1] = temp;

    // ��ְ諸�j�p
    (*n)--;
    // �״_�̤p�諸�ʽ�
    minHeap(arr,*n,0);

   
}

item_ptr findMin(item_ptr node) {
    while (node->leftchild != NULL) {
        node = node->leftchild;
    }
    return node;
}

item_ptr deleteNode(item_ptr root, const char* key) {
    if (root == NULL) {
        return root;
    }

    // ���n�R�����`�I
    if (cmp_(key, root->item_name) < 0) {
        root->leftchild = deleteNode(root->leftchild, key);
    } else if (cmp_(key, root->item_name) > 0) {
        root->rightchild = deleteNode(root->rightchild, key);
    } else {
        // �`�I�O���l�`�I�Υu���@�Ӥl�`�I�����p
        if (root->leftchild == NULL) {
            item_ptr temp = root->rightchild;
            free(root);
            return temp;
        } else if (root->rightchild == NULL) {
            item_ptr temp = root->leftchild;
            free(root);
            return temp;
        }

        // �`�I����Ӥl�`�I�����p�A���k�l�𪺳̤p�`�I
        item_ptr temp = findMin(root->rightchild);

        // �ƻs�̤p�`�I���Ȩ��e�`�I
        strcpy(root->item_name, temp->item_name);
        root->seller_count = temp->seller_count;
        for (int i = 0; i < temp->seller_count; ++i) {
            strcpy(root->seller_heap[i].SID, temp->seller_heap[i].SID);
            root->seller_heap[i].price = temp->seller_heap[i].price;
        }

        // �R���k�l�𪺳̤p�`�I
        root->rightchild = deleteNode(root->rightchild, temp->item_name);
    }

    return root;
}



void buy(item_ptr *root,const char* buyItemName,FILE* buyTable){
    if(*root == NULL){
        fprintf(buyTable,"%s doesn't exist!\n",buyItemName);
        buyfailtime++;
        return;
    }
    else if(cmp_(buyItemName,(*root)->item_name) == 0){

        if((*root)->seller_count > 0){//�p�G�o�Ӱӫ~����a�j��0
            //printf("%s %s %d\n",buyItemName,(*root)->seller_heap[0].SID,(*root)->seller_heap[0].price);
            fprintf(buyTable,"%s %s %d\n",(*root)->item_name,(*root)->seller_heap[0].SID,(*root)->seller_heap[0].price);
            deleteseller((*root)->seller_heap, &(*root)->seller_count);
            

            if((*root)->seller_count == 0){//�p�G�o�Ӱӫ~�S����a�N�R��
                item_ptr tmp = *root;
                *root = deleteNode(*root,buyItemName);
            }
        }
    }
    else if(cmp_(buyItemName,(*root)->item_name) < 0){
        buy(&(*root)->leftchild,buyItemName,buyTable);
    }
    else{
        buy(&(*root)->rightchild,buyItemName,buyTable);
    }
}

void inorder(item_ptr root, FILE* sort) {
    if (root != NULL) {
        inorder(root->leftchild, sort);
        fprintf(sort, "%s\n", root->item_name);
        inorder(root->rightchild, sort);
    }
}

int countNodes(item_ptr root) {
    if (root == NULL) {
        return 0;
    } 
    else {
        return 1 + countNodes(root->leftchild) + countNodes(root->rightchild);
    }
}

int counthighoftree(item_ptr root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = counthighoftree(root->leftchild);
        int rightDepth = counthighoftree(root->rightchild);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }
}

void report(item_ptr root, FILE *searchTable, FILE *buyTable, FILE *sortTable, FILE *logTable) {
    fprintf(logTable,"insert %d\n",insertime);
    fprintf(logTable,"search %d %d\n",searchtime,searchfailtime);
    fprintf(logTable,"buy %d %d\n",buytime,buyfailtime);
    fprintf(logTable,"node_num %d\n",countNodes(root));
    fprintf(logTable,"height %d\n",counthighoftree(root));
}

int main() {

    FILE* inputTable = fopen("input.txt", "r+");
    FILE* searchTable = fopen("SearchTable.txt", "w+");
    FILE* buyTable = fopen("BuyTable.txt", "w+");
    FILE* sortTable = fopen("SortTable.txt", "w+");
    FILE* logTable = fopen("LogTable.txt", "w+");

    char commend[100];
    item_ptr treeee = NULL;

    while (fscanf(inputTable, "%s", commend) != EOF) {

        if (strncmp("insert", commend, 6) == 0) {
            insertime++;
            char itemName[100];
            char sellerName[100];
            int itemprice = 0;
            fscanf(inputTable, "%s %s %d", itemName, sellerName, &itemprice);
            treeee = insert(treeee, itemName, sellerName, itemprice);
            
        }
        else if (strncmp("buy", commend, 3) == 0) {
            buytime++;
            char buyItemName[100];
            fscanf(inputTable, "%s", buyItemName);
            buy(&treeee,buyItemName,buyTable);

        }
        else if (strncmp("search", commend, 6) == 0) {
            searchtime++;
            char searchItemName[100];
            fscanf(inputTable, "%s", searchItemName);
            search(treeee,searchItemName,searchTable);

        }
        else if (strncmp("sort", commend, 4) == 0) {
            inorder(treeee,sortTable);
            fprintf(sortTable,"------------------------------\n");

        }
        else if (strncmp("report", commend, 6) == 0) {
            report(treeee,searchTable,buyTable,sortTable,logTable);
        }
        else {
            // printf("#error %s\n", commend);
        }
    }

    fclose(inputTable);
    fclose(searchTable);
    fclose(buyTable);
    fclose(sortTable);
    fclose(logTable);

    return 0;
}