#include<stdio.h>
#define MAX_QUEUE_SIZE 10
int global_clock = 0;

typedef struct Bank{
    int status; //�d�x���A  0 = close , 1 = open
    int queue[MAX_QUEUE_SIZE]; 
    int people_num; //�d�x�H��
    int left_time; //�Ѿl�ɶ�
}Bank;

typedef struct Customer {
    char id[20]; // �Ȥ�id
    int arr_time; // ��F�ɶ�
    int ser_time; // �n�B�z���ɶ�
}Customer;

Bank table[10];
Customer people[100];

// ��}�ۥB�ƶ��H�Ƴ̤֪��d�x
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
    FILE* input = fopen("input1.txt","r+");
        int windows; // �d�i��
        int all_people = 0; // �������H��

        fscanf(input,"%d",&windows);
        int window_hold = windows+1;
        // ��l���d�x
        while(window_hold--){
            table[window_hold-1].status = 1;
            table[window_hold-1].people_num = 0;
        }

        //�p�⦳�h�֤H�n�i�Ȧ� 
        int i = 0;
        while(fscanf(input,"%s %d %d",people[i].id,&people[i].arr_time,&people[i].ser_time)!=EOF){
            if (people[i].id[0]!='#'&&people[i].id[0]!='@'){
                all_people++;
            }
            i++;
        }

        int now = 0;

        while(all_people > 0){
            
            // printf("%d : %s ; %s\n",global_clock,(table[0].people_num > 0 ?  people[table[0].queue[0]].id : "NULL" ),(table[1].people_num > 0 ?  people[table[1].queue[0]].id : "NULL" ));

            global_clock++;

            if(people[now].arr_time == global_clock){

                // ���d�x
                if(people[now].id[0] == '#'){
                    
                    table[people[now].ser_time].status = 0;
                    // �Y�n�����d�x�ƶ��H�ƶW�L1�H �N�L����}�ۥB�H�Ƴ̤֪��d�x
                    while(table[people[now].ser_time].people_num > 1){

                        int move = findmin(table,windows);

                        table[move].queue[table[move].people_num-1] = table[people[now].ser_time].queue[1];
                        table[move].people_num++;

                        // �Y�d�x��1�H �N�L�n�B�z���ɶ���J�Ѿl�ɶ���
                        if ( table[move].people_num == 1){
                            table[move].left_time = people[table[0].people_num].ser_time+1;
                        }

                        for( int i = 1 ; i != table[people[now].ser_time].people_num ; i++ ){
                            table[people[now].ser_time].queue[i] = table[people[now].ser_time].queue[i+1];
                        }
                        table[people[now].ser_time].people_num--;
                    }
                }
                // �}�d�x
                else if(people[now].id[0] == '@'){
                    table[people[now].ser_time].status = 1;
                }
                // ��i�d�x�ƶ�
                else{
                    int min = findmin(table,windows);
                    // printf("%s,%d put in\n",people[now].id,min);
                    //printf("in\n");
                    table[min].queue[table[min].people_num] = now;
                    table[min].people_num++;
                    
                    //printf("ww%d,%d\n",min,table[min].left_time);
                    // �Y�d�x��1�H �N�L�n�B�z���ɶ���J�Ѿl�ɶ���
                    if(table[min].people_num == 1){
                        table[min].left_time = people[now].ser_time+1;
                        //printf("ww%d,%d\n",min,table[min].left_time);
                    }
                }
                now++;
            }
            // �N�C���d�x��e�B�z�H���Ѿl�ɶ���1
            for(int i = 0;i < windows;i++){
                if(table[i].people_num > 0){
                    table[i].left_time--;
                }
            }

            // �N�B�z�����H�L�X
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