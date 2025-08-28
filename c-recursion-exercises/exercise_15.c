/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Soma de dois números naturais, através de incrementos sucessivos.
 */
#include <stdio.h>

// Função recursiva para somar por incrementos sucessivos
int soma_incremento(int a, int b) {
    if (a < 0 || b < 0) {
        return -1; // Apenas para números naturais
    }
    if (b == 0) {
        return a;
    }
    // Incrementa 'a' e decrementa 'b' até 'b' chegar a 0
    return soma_incremento(a + 1, b - 1);
}

int main() {
    int a, b;
    printf("Digite dois números naturais para somar: ");
    scanf("%d %d", &a, &b);

    int resultado = soma_incremento(a, b);

    if (resultado == -1) {
        printf("Este programa funciona apenas com números naturais (não negativos).\n");
    } else {
        printf("%d + %d = %d\n", a, b, resultado);
    }

    return 0;
}
