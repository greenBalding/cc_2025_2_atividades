// MATHEUS SILVA PAINS
// 02/09/2025
// 1. Faça uma função recursiva que receba um número inteiro positivo N e imprima todos os números naturais de 0 até N em ordem crescente.

#include <stdio.h>

// Essa função imprime números de 0 até n em ordem crescente
void imprimir_crescente(int n) {
    if (n >= 0) {
        imprimir_crescente(n - 1);
        printf("%d ", n);
    }
}

// Na função main, lê o valor de N e chama a função recursiva
int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O número precisa ser > 0.\n");
        return 1;
    }

    imprimir_crescente(n);

    return 0;
}
