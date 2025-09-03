// MATHEUS SILVA PAINS
// 02/09/2025
// 2. Faça uma função recursiva que receba um número inteiro positivo N e imprima todos os números naturais de 0 até N em ordem decrescente.

#include <stdio.h>

// Essa função imprime números de n até 0 em ordem decrescente
void imprimir_decrescente(int n) {
    if (n >= 0) {
        printf("%d ", n);
        imprimir_decrescente(n - 1);
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

    imprimir_decrescente(n);

    return 0;
}
