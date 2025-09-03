// MATHEUS SILVA PAINS
// 02/09/2025
// 6. Faça uma função recursiva que implemente o gerador da sequência dada por:
// a. F(1) = 1
// b. F(2) = 2
// c. F(n) = 2*F(n - 1) + 3*F(n -2 ).

#include <stdio.h>

// Essa função implementa o gerador de sequencia para cada um dos casos
int gerador_sequencia(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    return 2 * gerador_sequencia(n - 1) + 3 * gerador_sequencia(n - 2);
}

// Na função main, lê o valor de N e chama a função recursiva. Se o valor informado for <= 0, exibe uma mensagem de erro.
int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O número precisa ser > 0.\n");
    } else {
        int resultado = gerador_sequencia(n);
        printf("N na sequência é %d.\n", n, resultado);
    }

    return 0;
}
