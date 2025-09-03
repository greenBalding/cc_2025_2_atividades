// MATHEUS SILVA PAINS
// 02/09/2025
// 8. Gerador de máximo divisor comum (mdc):
// A. mdc(x, y) = y, se x >= y e x mod y = 0
// B. mdc(x, y) = mdc(y, x), se x < y
// C. mdc(x, y) = mdc(y, x mod y), caso contrário.

#include <stdio.h>

// Essa função calcula o máximo divisor comum (mdc) entre x e y de forma recursiva
int mdc(int x, int y) {
    if (x < y) {
        return mdc(y, x); // Caso B
    }
    if (x % y == 0 && x >= y) {
        return y; // Caso A
    }
    return mdc(y, x % y); // Caso C
}

// Na função main, lê os valores de X e Y e chama a função recursiva. Se Y for 0, o mdc é X. Se X for 0, o mdc é Y.
int main() {
    int x, y;
    printf("Digite X depois Y: ");
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
