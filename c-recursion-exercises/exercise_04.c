// MATHEUS SILVA PAINS
// 02/09/2025 
//4. Faça uma função recursiva que calcule e retorne o N-ésimo termo da sequência Fibonacci. Alguns números desta sequência são: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89...


#include <stdio.h>

// Essa função calcula o n-ésimo termo da sequência Fibonacci de forma recursiva
int fibonacci(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Na função main, lê o valor de N e chama a função recursiva. Se o valor informado for < 0, exibe uma mensagem de erro.
int main() {
    int n;
    printf("N: ");
    scanf("%d", &n);

    int resultado = fibonacci(n);

    if (resultado == -1) {
        printf("O número precisa ser > 0.\n");
    } else {
        printf("N na sequencia de Fibonacci é %d.\n", n, resultado);
    }

    return 0;
}
