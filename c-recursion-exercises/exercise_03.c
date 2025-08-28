/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Calcula e retorna o fatorial de um número inteiro N.
 */
#include <stdio.h>

// Função recursiva para calcular o fatorial
long long fatorial(int n) {
    if (n < 0) {
        return -1; // Fatorial de número negativo não é definido
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}

int main() {
    int n;
    printf("Digite um número inteiro para calcular o fatorial: ");
    scanf("%d", &n);

    long long resultado = fatorial(n);

    if (resultado == -1) {
        printf("Fatorial não é definido para números negativos.\n");
    } else {
        printf("O fatorial de %d é %lld.\n", n, resultado);
    }

    return 0;
}
