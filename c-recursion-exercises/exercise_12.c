/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Calcula o N-ésimo termo da sequência de Tribonacci.
 * Observação: A definição exata não foi fornecida (imagem ausente).
 * Esta implementação usa a definição T(0)=0, T(1)=1, T(2)=1.
 */
#include <stdio.h>

// Função recursiva para o N-ésimo termo de Tribonacci
int tribonacci(int n) {
    if (n < 0) {
        return -1; // Posição inválida
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}

int main() {
    int n;
    printf("Digite o termo (N) da sequência de Tribonacci: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O termo N deve ser um inteiro não negativo.\n");
    } else {
        int resultado = tribonacci(n);
        printf("O %d-ésimo termo da sequência de Tribonacci é %d.\n", n, resultado);
    }

    return 0;
}
