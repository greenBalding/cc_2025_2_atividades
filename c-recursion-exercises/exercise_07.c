/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Implementa o gerador de Sequência de Ackerman.
 */
#include <stdio.h>

// Função recursiva de Ackermann
int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else if (m > 0 && n > 0) {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
    return -1; // Caso de erro (m ou n negativos)
}

int main() {
    int m, n;
    printf("Digite dois inteiros não negativos (m e n) para a função de Ackermann: ");
    scanf("%d %d", &m, &n);

    if (m < 0 || n < 0) {
        printf("Os números devem ser não negativos.\n");
    } else {
        // A função de Ackermann cresce muito rápido.
        // Valores de m >= 4 podem ser computacionalmente inviáveis.
        printf("A(%d, %d) = %d\n", m, n, ackermann(m, n));
    }

    return 0;
}
