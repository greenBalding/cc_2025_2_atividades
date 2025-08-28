/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Multiplicação de dois números naturais através de somas sucessivas.
 */
#include <stdio.h>

// Função recursiva para multiplicar por somas sucessivas
int multiplicacao_soma(int a, int b) {
    if (a < 0 || b < 0) {
        return -1; // Apenas para números naturais
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    // Para otimizar, podemos iterar o menor número de vezes
    if (a < b) {
        return multiplicacao_soma(b, a);
    }
    return a + multiplicacao_soma(a, b - 1);
}

int main() {
    int a, b;
    printf("Digite dois números naturais para multiplicar: ");
    scanf("%d %d", &a, &b);

    int resultado = multiplicacao_soma(a, b);

    if (resultado == -1) {
        printf("Este programa funciona apenas com números naturais (não negativos).\n");
    } else {
        printf("%d * %d = %d\n", a, b, resultado);
    }

    return 0;
}
