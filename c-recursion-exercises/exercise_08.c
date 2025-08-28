/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Gerador de máximo divisor comum (mdc).
 */
#include <stdio.h>

// Função recursiva para o mdc
int mdc(int x, int y) {
    if (x < y) {
        return mdc(y, x); // mdc(x, y) = mdc(y, x), se x < y
    }
    // se x >= y e x mod y = 0, y é o mdc
    if (x % y == 0) {
        return y;
    }
    // mdc(x, y) = mdc(y, x mod y), caso contrário
    return mdc(y, x % y);
}

int main() {
    int x, y;
    printf("Digite dois inteiros para encontrar o MDC: ");
    scanf("%d %d", &x, &y);

    if (y == 0) {
        printf("MDC de %d e %d é %d\n", x, y, x);
    } else if (x == 0) {
        printf("MDC de %d e %d é %d\n", x, y, y);
    } else {
        printf("MDC de %d e %d é %d\n", x, y, mdc(x, y));
    }

    return 0;
}
