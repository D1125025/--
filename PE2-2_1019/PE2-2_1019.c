#include <stdio.h>

int find(int n, int m, int p) {
    int survivor = 0;
    for (int i = 2; i <= n; i++) {
        survivor = (survivor + m) % i;
    }
    return (survivor + p) % n;
}

int main() {
    int n, m, p;
    while (1) {
        scanf("%d %d %d", &n, &m, &p);
        if (n == 0 && m == 0) {
            break;
        }
        int player = find(n, m, p);
        if(player == 0){
            player += n;
        }
        printf("%d\n", player);
    }
    return 0;
}
