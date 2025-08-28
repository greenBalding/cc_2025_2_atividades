/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Imprime todos os números naturais de N até 0 em ordem decrescente.
 */
#include <stdio.h>

// Função recursiva para imprimir números em ordem decrescente
void imprimir_decrescente(int n) {
    if (n >= 0) {
        printf("%d ", n);
        imprimir_decrescente(n - 1);
    }
}

int main() {
    int n;
    printf("Digite um número inteiro positivo N: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O número deve ser positivo.\n");
        return 1;
    }

    printf("Números de %d a 0 em ordem decrescente: ", n);
    imprimir_decrescente(n);
    printf("\n");

    return 0;
}
