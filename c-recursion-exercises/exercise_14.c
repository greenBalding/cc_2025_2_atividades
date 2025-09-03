// MATHEUS SILVA PAINS
// 02/09/2025
// 14. Multiplicação de dois números naturais, através de somas sucessivas(Ex.: 6 x 4 = 4 + 4 + 4 + 4 + 4 + 4).

#include <stdio.h>

int multiplicacao_soma(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    if (a < b) {
        return multiplicacao_soma(b, a);
    }
    return a + multiplicacao_soma(a, b - 1);
}

int main() {
    int a, b;
    printf("Digite 2 números: ");
    scanf("%d %d", &a, &b);

    int resultado = multiplicacao_soma(a, b);

    if (resultado == -1) {
        printf("O número precisa ser >= 0.\n");
    } else {
        printf("%d * %d = %d\n", a, b, resultado);
    }

    return 0;
}
