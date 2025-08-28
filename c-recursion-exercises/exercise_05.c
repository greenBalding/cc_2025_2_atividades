/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Cálculo de 1 + 1/2 + 1/3 + 1/4 + ... + 1/N.
 */
#include <stdio.h>

// Função recursiva para calcular a soma da série
double soma_serie(int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (n == 1) {
        return 1.0;
    }
    return (1.0 / n) + soma_serie(n - 1);
}

int main() {
    int n;
    printf("Digite um número inteiro positivo N para a soma da série: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O número deve ser um inteiro positivo.\n");
    } else {
        double resultado = soma_serie(n);
        printf("A soma da série até 1/%d é %f.\n", n, resultado);
    }

    return 0;
}
