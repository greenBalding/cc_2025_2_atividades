/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Imprime todos os números naturais de 0 até N em ordem crescente.
 */
#include <stdio.h>

// Função recursiva para imprimir números em ordem crescente
void imprimir_crescente(int n) {
    if (n >= 0) {
        imprimir_crescente(n - 1);
        printf("%d ", n);
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

    printf("Números de 0 a %d em ordem crescente: ", n);
    imprimir_crescente(n);
    printf("\n");

    return 0;
}
