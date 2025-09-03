// MATHEUS SILVA PAINS
// 02/09/2025
// 12. Faça uma função recursiva que receba um número N e retorne o N-ésimo termo da sequência de tribonacci

#include <stdio.h>

int f(int n) {
    if (n < 0) {
        return -1; // Caso inválido
    }
    if (n == 0) {
        return 0; // Caso 1
    }
    if (n == 1) {
        return 0; // Caso 2
    }
    if (n == 2) {
        return 1; // Caso 3
    }
    return f(n - 1) + f(n - 2) + f(n - 3);
}

int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O número precisa ser > 0.\n");
    } else {
        int resultado = f(n);
        printf("N sequência de f é %d.\n", n, resultado);
    }

    return 0;
}
