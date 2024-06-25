#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PERSONS 1000

int arr[MAX_PERSONS][MAX_PERSONS];
int number[MAX_PERSONS];

void initGraph(int P) {
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < P; ++j) {
            arr[i][j] = 0;
        }
    }
}

void addEdge(int person1, int person2) {
    arr[person1][person2] = 1;
    arr[person2][person1] = 1;
}

void DonGiovanniNumbers(int P) {
    for (int i = 1; i < P; ++i) {
        number[i] = -1;
    }
    
    number[0] = 0;
    bool visited[MAX_PERSONS] = {false};
    int queue[MAX_PERSONS];
    int front = 0, rear = 0;

    queue[rear++] = 0;
    visited[0] = true;

    while (front < rear) {
        int currentPerson = queue[front++];
        
        for (int neighbor = 0; neighbor < P; ++neighbor) {
            if (arr[currentPerson][neighbor] && !visited[neighbor]) {
                number[neighbor] = number[currentPerson] + 1;
                queue[rear++] = neighbor;
                visited[neighbor] = true;
            }
        }
    }
}

int main() {
    int testCases;
    scanf("%d", &testCases);

    for (int t = 0; t < testCases; ++t) {
        int P, D;
        scanf("%d %d", &P, &D);
        
        initGraph(P);

        for (int d = 0; d < D; ++d) {
            int person1, person2;
            scanf("%d %d", &person1, &person2);
            addEdge(person1, person2);
        }

        DonGiovanniNumbers(P);

        for (int i = 1; i < P; ++i) {
            printf("%d\n", number[i]);
        }

        if (t < testCases - 1) {
            printf("\n");
        }
    }

    return 0;
}
