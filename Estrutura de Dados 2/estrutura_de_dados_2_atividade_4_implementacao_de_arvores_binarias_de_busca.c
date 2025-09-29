// N1 - Atividade 04 - Implementação de Árvores Binárias de Busca
// Nome: MATHEUS SILVA PAINS - 2024.2.0028.0032-0

/* 

Instruções: Implemente as funções conforme requisitado: 

- Inserir nós na árvore binária de busca.
- Busca em largura (BFS - Breadth-First Search) iterativa em árvores binárias
- Verificar se um item existe na árvore
- Retornar valores MAX e MIN

*/

#include <stdio.h>
#include <stdlib.h>

// 1º vamos criar a struct pro node

typedef struct Node {
    int nodeValor;
    struct Node* esquerda;
    struct Node* direita;
};

// 2º vamos criar a funcao para criar um novo node

struct Node* novoNode(int valor) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // vamo mallocar a memoria pro node

    node->nodeValor = valor; // ai aqui a gente atribui o valor para o node. Na verdade o usuário vai passar o valor na hora de selecionar a opção 1
    node->esquerda = NULL; // seta o filho da esquerda como vazio
    node->direita = NULL; // seta o filho da direita como vazio

    return node; // retorna então a struct do node
}

// 3º vamos criar as funções do menu de opções

// função opcao_1: insert node
// Para isso vamos criar uma função que irá de forma recursiva inserir e atualizar os ponteiros da arvore

struct Node* insertNode(struct Node* raiz, int valor) {

    // Primeiro coisa é verificar se a raiz é nula. Ou seja, se a arvore está vazia
    if (raiz == NULL)
    {
        return novoNode(valor); // se estiver vazia, a gente cria um novo node com o valor passado e retorna ele
    }
    // Ai caso a arvore não esteja vazia, ou tenha passado pelo primeiro caso, a gente pode começar a inserir os valores com base no valor raiz e fazer as comparações
    if (valor < raiz->nodeValor) 
    {
        raiz->esquerda = insertNode(raiz->esquerda, valor); // se o valor for menor que o valor da raiz, a gente insere ele na subarvore esquerda
    } else if (valor > raiz->nodeValor) 
    {
        raiz->direita = insertNode(raiz->direita, valor); // se o valor for maior que o valor da raiz, a gente insere ele na subarvore direita

    }

    return raiz; // se o valor for igual, a gente não faz nada e retorna a raiz
};

// função opcao_2: breadth search (BFS - Busca em Largura)

// função opcao_3: verify item

// função opcao_4: get MAX / MIN

// Função principal

int main() {

    int opcao;
    struct Node* raiz = NULL; // inicializa a raiz como nula

    do {
        printf("[Selecione uma Operação]\n");
        printf("1 - Insert Node\n");
        printf("2 - Breadth Search (Busca em Largura)\n");
        printf("3 - Verify item\n");
        printf("4 - Get MIN / MAX\n");
        printf("5 - Exit\n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Digite o valor para o nó: \n");
                int valor;
                scanf("%d", &valor);
                raiz = insertNode(raiz, valor);
                printf("Nó inserido com sucesso!\n");
                break;
            case 2:
                // Código para busca em largura (BFS)
                break;
            case 3:
                // Código para verificar se item existe
                break;
            case 4:
                // Código para retornar MAX e MIN
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);
    return 0;
}