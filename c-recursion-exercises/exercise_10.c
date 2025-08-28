/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Soma os elementos de um vetor de inteiros.
 */
#include <stdio.h>

// Função recursiva para somar os elementos de um vetor
int somar_vetor(int vetor[], int tamanho) {
    if (tamanho <= 0) {
        return 0;
    }
    // Soma o último elemento com a soma do resto do vetor
    return vetor[tamanho - 1] + somar_vetor(vetor, tamanho - 1);
}

int main() {
    int vetor[] = {10, 20, 30, 40, 50};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    int soma = somar_vetor(vetor, tamanho);
    printf("A soma dos elementos do vetor é: %d\n", soma);

    return 0;
}
