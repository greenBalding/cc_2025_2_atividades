/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Implementa o gerador da sequência F(n) = 2*F(n-1) + 3*F(n-2).
 */
#include <stdio.h>

// Função recursiva para a sequência dada
int gerador_sequencia(int n) {
    if (n <= 0) {
        return 0; // Ou algum valor de erro, pois a definição é para n >= 1
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    return 2 * gerador_sequencia(n - 1) + 3 * gerador_sequencia(n - 2);
}

int main() {
    int n;
    printf("Digite o termo (N) da sequência a ser calculado: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O termo N deve ser um inteiro positivo.\n");
    } else {
        int resultado = gerador_sequencia(n);
        printf("O %d-ésimo termo da sequência é %d.\n", n, resultado);
    }

    return 0;
}
