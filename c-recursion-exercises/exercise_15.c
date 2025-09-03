// MATHEUS SILVA PAINS
// 02/09/2025
// 15. Soma de dois números naturais, através de incrementos sucessiv (Ex.: 3 + 2 = + + (+ + 3)).

#include <stdio.h>

int soma_incremento(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    if (b == 0) {
        return a;
    }
    return soma_incremento(a + 1, b - 1);
}

int main() {
    int a, b;
    printf("Digite 2 números: ");
    scanf("%d %d", &a, &b);

    int resultado = soma_incremento(a, b);

    if (resultado == -1) {
        printf("O número precisa ser >=0.\n");
    } else {
        printf("%d + %d = %d\n", a, b, resultado);
    }

    return 0;
}
