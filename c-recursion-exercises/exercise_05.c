// MATHEUS SILVA PAINS
// 02/09/2025
// 5. Cálculo de 1 + 1/2 + 1/3 + 1/4 + ... + 1/N.

#include <stdio.h>

// Essa função calcula a soma da série 1 + 1/2 + 1/3 + ... + 1/n de forma recursiva
double soma_serie(int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (n == 1) {
        return 1.0;
    }
    return (1.0 / n) + soma_serie(n - 1);
}

// Na função main, lê o valor de N e chama a função recursiva. Lembrando que N deve ser > 0.
int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O número precisa ser > 0\n");
    } else {
        double resultado = soma_serie(n);
        printf("A soma é %f.\n", n, resultado);
    }

    return 0;
}
