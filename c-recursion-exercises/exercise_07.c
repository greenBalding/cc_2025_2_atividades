// MATHEUS SILVA PAINS
// 02/09/2025
// 7. Faça uma função recursiva que implemente o gerador de Sequência de Ackerman:
// I. A(m, n) = n + 1, se m = 0
// II. A(m, n) = A(m - 1, 1), se m != 0 e n = 0
// III. A(m, n) = A(m - 1,A(m, n - 1)), se m != 0 e n != 0

#include <stdio.h>

int A(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m != 0 && n == 0) {
        return A(m - 1, 1);
    } else if (m != 0 && n > 0) {
        return A(m - 1, A(m, n - 1));
    }
    return -1;
}

int main() {
    int m, n;
    printf("Digite M depois N: ");
    scanf("%d %d", &m, &n);

    if (m < 0 || n < 0) {
        printf("O número precisa ser > 0.\n");
    } else {
        printf("A(%d, %d) = %d\n", m, n, A(m, n));
    }

    return 0;
}
