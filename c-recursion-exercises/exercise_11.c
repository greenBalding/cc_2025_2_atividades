/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Contém uma função recursiva que recebe dois inteiros
 *                positivos k e n e calcula k^n.
 */
#include <stdio.h>

// Função recursiva para calcular k^n usando multiplicações
long long potencia(int k, int n) {
    if (n < 0) {
        return -1; // Expoente negativo não é suportado nesta versão
    }
    if (n == 0) {
        return 1;
    }
    return k * potencia(k, n - 1);
}

int main() {
    int k, n;
    printf("Digite a base (k) e o expoente (n) [k e n positivos]: ");
    scanf("%d %d", &k, &n);

    if (k < 0 || n < 0) {
        printf("Este programa suporta apenas inteiros positivos para k e n.\n");
    } else {
        long long resultado = potencia(k, n);
        printf("%d^%d = %lld\n", k, n, resultado);
    }

    return 0;
}
