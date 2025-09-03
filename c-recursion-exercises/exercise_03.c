// MATHEUS SILVA PAINS
// 02/09/2025
// 3. Faça uma função recursiva que calcule e retorne o fatorial de um número inteiro N.

#include <stdio.h>

// Essa função calcula o fatorial de n de forma recursiva
long long fatorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}

// Na função main, lê o valor de N e chama a função recursiva. Se o valor informado for < 0, exibe uma mensagem de erro.
int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    long long resultado = fatorial(n);

    if (resultado == -1) {
        printf("O número precisa ser > 0.\n");
    } else {
        printf("O fatorial de %d é %lld.\n", n, resultado);
    }

    return 0;
}
