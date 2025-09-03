// MATHEUS SILVA PAINS
// 02/09/2025
// 10. Faça uma função recursiva que permita somar os elementos de um vetor de inteiros.

#include <stdio.h>

int somar_vetor(int vetor[], int tamanho) {
    if (tamanho <= 0) {
        return 0;
    }
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
    printf("A soma do vetor é: %d\n", soma);

    return 0;
}
