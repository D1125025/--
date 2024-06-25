#include <stdio.h>

int find(char array[],char c,int n) {
    for (int i = 0;i < n;i++)
        if (array[i] == c){
            return i;
        }
    return -1;
}

void postprint(char in[],char pre[],int n,FILE *output) {
    if (n == 0){
        return;
    }

    int root = find(in,pre[0],n);
    if (root == -1) {
        return;
    }
    postprint(in,pre+1,root,output);
    postprint(in+root+1,pre+root+1,n-root-1,output);
    fprintf(output,"%c",pre[0]);
}

int main() {
    FILE *in = fopen("in.txt","r+");
    FILE *out = fopen("out.txt","w+");

    int num;
    fscanf(in,"%d",&num);

    char preorder[60];
    char inorder[60];
    fscanf(in,"%s",preorder);
    fscanf(in,"%s",inorder);

    postprint(inorder,preorder,num,out);

    fclose(in);
    fclose(out);

    return 0;
}

// // ABDGHECFIJ
// // GDHBEACIFJ

// // GHDEBIJFCA


// // ABDGHECFIJ �����k
// // GDHBEACIFJ �����k
// // �n�ܥ��k��
// // �NB�s������� C�s���k���
// // ��k�]��k��� 
// // ��: A B D G H E C F I J
// // ��: B D G H E C F I J
// // �k: C E H D B A I J F
// // 
// // 1.A
// // GDHBE
// // A
// // CIFJ

// // 2.B
// // GDH
// // B
// // E
// // A
// // CIFJ
// // 
// // 3.D
// // G
// // D
// // H
// // B
// // E
// // A
// // CIFJ

