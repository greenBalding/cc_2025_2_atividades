/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Calcula e retorna o N-ésimo termo da sequência Fibonacci.
 */
#include <stdio.h>

// Função recursiva para calcular o N-ésimo termo de Fibonacci
int fibonacci(int n) {
    if (n < 0) {
        return -1; // Posição inválida
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    printf("Digite a posição (N) na sequência de Fibonacci: ");
    scanf("%d", &n);

    int resultado = fibonacci(n);

    if (resultado == -1) {
        printf("A posição deve ser um número não negativo.\n");
    } else {
        printf("O %d-ésimo termo da sequência de Fibonacci é %d.\n", n, resultado);
    }

    return 0;
}
