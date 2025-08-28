/*
 * Autor: Jules
 * Data: 28/08/2025
 * Funcionalidade: Inverte um número inteiro N. Ex: 123 -> 321.
 */
#include <stdio.h>

// Função auxiliar recursiva
int inverter_recursivo(int n, int reverso) {
    if (n == 0) {
        return reverso;
    }
    int ultimo_digito = n % 10;
    return inverter_recursivo(n / 10, reverso * 10 + ultimo_digito);
}

// Função principal que chama a função recursiva
int inverter(int n) {
    return inverter_recursivo(n, 0);
}

int main() {
    int n;
    printf("Digite um número inteiro para inverter: ");
    scanf("%d", &n);

    int resultado = inverter(n);
    printf("O número %d invertido é %d.\n", n, resultado);

    return 0;
}
