// #include<stdio.h>
// #define MAX_QUEUE_SIZE 10
// int global_clock = 0;

// typedef struct Bank{
//     int status;
//     int queue[MAX_QUEUE_SIZE];
//     int people_num;
//     int left_time;
// }Bank;

// typedef struct Customer {
//     char id[20]; // �Ȥ� id
//     int arr_time; // �Ȥ��F�Ȧ�ɶ�
//     int ser_time; // �Ȥ᧹���~�ȭn��h�֮ɶ�
// }Customer;

// Bank table[10];
// Customer people[100];

// int findmin(Bank a[],int windows){
//     int x = 1;
//     int turn_back = 0;
//     while(x < windows){
//         if(a[x].status == 1){
//             if(a[x].people_num < a[turn_back].people_num){
//                 turn_back = x;
//             } 
//         }
        
//         x++;  
//     } 
//     return turn_back;
// }

// int main(){
//     FILE* input = fopen("input1.txt","r+");
//         int windows;
        
//         fscanf(input,"%d",&windows);
//         int window_hold = windows;
//         while(window_hold--){
//             table[window_hold-1].status = 1;
//             table[window_hold-1].people_num = 0;
//         }
//         int i = 0;
//         while(fscanf(input,"%s %d %d",people[i].id,&people[i].arr_time,&people[i].ser_time)!=EOF){
//             i++;
//         }
//         // while(i--){
//         // printf("%s %d %d\n",people[i].id,people[i].arr_time,people[i].ser_time);
//         // }

//         int all_people = i-1;
//         int now = 0;//�{�b���b�B�z���H
//         while(all_people != 0){
//             global_clock++;
//             // ��ɶ������b�B�z�H����F�ɶ���
//             if(people[now].arr_time == global_clock){

//                 //�P�w�n��H��i�h�٬O�}���Ȧ�
//                 if(people[now].id[0] == '#'){
//                     table[people[now].ser_time].status = 0;
//                     //�Y�n�������d�x���u�@�H �N�٨S�B�z���H���̤֤H���d�i
//                     while(table[people[now].ser_time].people_num > 1){
//                         int move = findmin(table,windows);
//                         table[move].queue[table[move].people_num-1] = table[people[now].ser_time].queue[1];
//                         table[move].people_num++;

//                         for(int i = 1;i != table[people[now].ser_time].people_num;i++){
//                             table[people[now].ser_time].queue[i] = table[people[now].ser_time].queue[i+1];
//                         }
//                         table[people[now].ser_time].people_num--;
//                     }
//                 }
//                 else if(people[now].id[0] == '@'){
//                     table[people[now].ser_time].status = 1;
//                 }
//                 else{
//                     //printf ("%d",findmin(table,windows));
//                     int min = findmin(table,windows);
//                     table[min].queue[table[min].people_num] = now;
//                     table[min].people_num++;
                    
//                     if(table[min].people_num == 1){
//                         table[min].left_time = people[now].ser_time;
//                     }
//                 }
//                 now++;
//             }
            
//             for(int i = 0;i < windows;i++){
//                 if(table[i].people_num > 0){
//                     table[i].left_time--;
//                 }
//             }

//             for(int i = 0;i < windows;i++){

//                 if(table[i].left_time == 0){
//                     printf("%s %d %d\n",people[table[i].queue[0]].id,global_clock,i);
//                     all_people--;
//                     table[i].people_num--;
                    
//                     if(table[i].people_num > 0){
//                         for(int j = 0; j < table[i].people_num ;j++){
//                             table[i].queue[j] = table[i].queue[j+1];
//                         }
//                     }

                    
//                 }
//             }
//         }
// }


#include<stdio.h>
#define MAX_QUEUE_SIZE 10
int global_clock = 0;

typedef struct Bank{
    int status;
    int queue[MAX_QUEUE_SIZE];
    int people_num;
    int left_time;
}Bank;

typedef struct Customer {
    char id[20]; // ??? id
    int arr_time; // ????F?????
    int ser_time; // ??????~??n??h????
}Customer;

Bank table[10];
Customer people[100];

int findmin(Bank a[],int windows){
    
    int x = 1;
    int turn_back = 0;

    while(x < windows){
        if(a[x].status == 1){
            if(a[x].people_num < a[turn_back].people_num){
                turn_back = x;
            } 
        }
        x++;  
    } 
    return turn_back;
}

int main(){
    FILE* input = fopen("input2.txt","r+");
        int windows;
        
        fscanf(input,"%d",&windows);
        int window_hold = windows;
        while(window_hold--){
            table[window_hold-1].status = 1;
            table[window_hold-1].people_num = 0;
        }
        int i = 0;
        while(fscanf(input,"%s %d %d",people[i].id,&people[i].arr_time,&people[i].ser_time)!=EOF){
            i++;
        }
        // while(i--){
        // printf("%s %d %d\n",people[i].id,people[i].arr_time,people[i].ser_time);
        // }

        int all_people = i-1;
        int now = 0;//?{?b???b?B?z???H
        while(all_people >= 0){
            global_clock++;

            //printf ("a%d\n",global_clock);
            //printf("f%d\n",table[0].people_num);

            if(people[now].arr_time == global_clock){

                if(people[now].id[0] == '#'){
                    table[people[now].ser_time].status = 0;

                    while(table[people[now].ser_time].people_num > 1){
                        int move = findmin(table,windows);

                        if(table[move].people_num == 0){
                            table[move].left_time = people[table[people[now].ser_time].queue[1]].ser_time;
                        }
                        table[move].queue[table[move].people_num-1] = table[people[now].ser_time].queue[1];
                        table[move].people_num++;

                        for(int i = 1;i != table[people[now].ser_time].people_num;i++){
                            table[people[now].ser_time].queue[i] = table[people[now].ser_time].queue[i+1];
                        }
                        table[people[now].ser_time].people_num--;
                    }
                }
                else if(people[now].id[0] == '@'){
                    table[people[now].ser_time].status = 1;
                }
                else{
                    int min = findmin(table,windows);
                    table[min].queue[table[min].people_num] = now;
                    table[min].people_num++;
                    
                    //printf("f%d\n",table[min].people_num);
                    if(table[min].people_num == 1){
                        table[min].left_time = people[now].ser_time;
                        //printf("ww%d\n",table[min].left_time);
                    }
                }
                now++;
            }
            
            for(int i = 0;i < windows;i++){
                if(table[i].people_num > 0){
                    table[i].left_time--;
                }
            }
            
            for (int i = 0;i < windows;i++){
                if( table[i].left_time == 0 && table[i].people_num > 0 ){

                    printf("%s %d %d\n",people[table[i].queue[0]].id,global_clock,i);
                    all_people--;

                    if(table[i].people_num != 0){
                        for(int j = 0; j < table[i].people_num ;j++){
                            table[i].queue[j] = table[i].queue[j+1];
                        }
                        table[i].left_time = people[table[i].queue[0]].ser_time;
                    }
                    table[i].people_num--;
                }
            }
        }
}