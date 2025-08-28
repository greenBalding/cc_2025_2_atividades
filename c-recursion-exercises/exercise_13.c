/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Calcula o N-ésimo termo da sequência de Padovan.
 */
#include <stdio.h>

// Função recursiva para o N-ésimo termo de Padovan
int padovan(int n) {
    if (n < 0) {
        return -1; // Posição inválida
    }
    if (n == 0 || n == 1 || n == 2) {
        return 1;
    }
    return padovan(n - 2) + padovan(n - 3);
}

int main() {
    int n;
    printf("Digite o termo (N) da sequência de Padovan: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O termo N deve ser um inteiro não negativo.\n");
    } else {
        int resultado = padovan(n);
        printf("O %d-ésimo termo da sequência de Padovan é %d.\n", n, resultado);
    }

    return 0;
}
