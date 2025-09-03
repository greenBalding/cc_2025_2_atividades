// MATHEUS SILVA PAINS
// 02/09/2025
// 9. Faça uma função recursiva que permita inverter um número inteiro N. Ex: 123 – 321

#include <stdio.h>

// Função auxiliar para inverter o número de forma recursiva
int inverter_recursivo(int n, int reverso) {
    if (n == 0) {
        return reverso;
    }
    int ultimo_digito = n % 10;
    return inverter_recursivo(n / 10, reverso * 10 + ultimo_digito);
}

// Função que vai iniciar a inversão
int inverter(int n) {
    return inverter_recursivo(n, 0);
}

// Na função main, lê o valor de N e chama a função de inversão
int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    int resultado = inverter(n);
    printf("O número invertido é %d.\n", n, resultado);

    return 0;
}
