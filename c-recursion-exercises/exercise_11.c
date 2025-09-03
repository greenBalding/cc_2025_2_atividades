// MATHEUS SILVA PAINS
// 02/09/2025
// 11. Crie um programa em C, que contenha uma função recursiva que receba dois inteiros positivos k e n e calcule kn . Utilize apenas multiplicações. O programa principal deve solicitar ao usuário os valores de k e n e imprimir o resultado da chamada da função.

#include <stdio.h>

long long potencia(int k, int n) {
    if (n < 0) {
        return -1;
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
        printf("k e n devem ser > 0.\n");
    } else {
        long long resultado = potencia(k, n);
        printf("%d^%d = %lld\n", k, n, resultado);
    }

    return 0;
}
