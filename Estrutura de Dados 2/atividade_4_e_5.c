// N1 - Atividade 04 - Implementação de Árvores Binárias de Busca
// N2 - Atividade 05 - Implementação de Árvores Binárias de Busca (continuação)
// Nome: MATHEUS SILVA PAINS - 2024.2.0028.0032-0

/* 

Instruções: Implemente as funções conforme requisitado: 

>>> Atividade 4 <<<
- Inserir nós na árvore binária de busca.
- Busca em largura (BFS - Breadth-First Search) iterativa em árvores binárias
- Verificar se um item existe na árvore
- Retornar valores MAX e MIN

>>> Atividade 5 <<<
- Depth Search (In Order)
- Depth Search (Pre Order)
- Depth Search (Pos Order)
- Depth Search (iterative Pre Order)
- Depth Search (iterative Pos Order)
- Depth Search (iterative In Order)

*/

// BIBLIOTECAS ---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

// CONSTRUTORES ---------------------------------------------------------------

// 1.1.1. vamos criar a struct pro node
typedef struct Node {
    int nodeValor;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// 1.1.2. vamos criar a funcao para criar um novo node
struct Node* nodeNovo(int valor) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // vamo mallocar a memoria pro node

    node->nodeValor = valor; // ai aqui a gente atribui o valor para o node. Na verdade o usuário vai passar o valor na hora de selecionar a opção 1
    node->esquerda = NULL; // seta o filho da esquerda como vazio
    node->direita = NULL; // seta o filho da direita como vazio

    return node; // retorna então a struct do node
}

// 1.2.1. vamos criar a struct para o nó da fila
typedef struct nodeFila {
    struct Node* nodePosicao;
    struct nodeFila* proximaPosicao;
} nodeFila;

// 1.2.2. vamos criar a struct da fila que permitirá que os nós sejam percorridos nível por nível
// A fila sempre terá o conhecimento do endereço do ínicio e do fim da fila
typedef struct Fila {
    struct nodeFila* inicio;
    struct nodeFila* fim;
} Fila;

// 1.2.3. vamos criar a função para criar uma nova fila
struct Fila* filaNovo() {
    struct Fila* fila = (struct Fila*)malloc(sizeof(struct Fila)); // vamo mallocar a memoria pra fila

    fila->inicio = NULL; // seta o inicio da fila como vazio
    fila->fim = NULL; // seta o fim da fila como vazio

    return fila; // retorna então a struct da fila
}

// 1.2.4. agora vamos criar a função para ADICIONAR o nodeFila na Fila
void filaAdicionarNode(Fila* fila, struct Node* node) {
    struct nodeFila* nodeFilaNovo = (struct nodeFila*)malloc(sizeof(struct nodeFila)); // vamo mallocar a memoria pro nodeFila

    // chama o construtor do nodeFila
    nodeFilaNovo->nodePosicao = node; // seta o nodePosicao do nodeFila como o node passado por parâmetro pelo usuário
    nodeFilaNovo->proximaPosicao = NULL; // seta o proximaPosicao como vazio

    // A fila está vazia?
    if (fila->fim == NULL) {
        fila->inicio = nodeFilaNovo; // se estiver vazia, o inicio da fila é o novo nodeFila
        fila->fim = nodeFilaNovo; // se estiver vazia, o fim da fila é o novo nodeFila. Ou seja, só tem um elemento na fila agora
    } else {
        // A fila não está vazia!
        fila->fim->proximaPosicao = nodeFilaNovo; // agora o proximaPosicao do fim da fila é o novo nodeFila
        fila->fim = nodeFilaNovo; // atualiza o fim da fila para o novo nodeFila, dado que antes o fim da fila era o penúltimo nodeFila
    }
}

// 1.2.5. agora vamos criar a função para REMOVER o nodeFila da Fila
struct Node* filaRemoverNode(Fila* fila) {
    // A fila está vazia?
    if (fila->inicio == NULL) {
        return NULL; // se estiver vazia, retorna vazio
    }

    // A fila não está vazia! Vamos precisar de algumas variáveis temporárias então para poder fazer a remoção
    struct nodeFila* temp = fila->inicio; // Lembre FIFO - Primeiro a Entrar, Primeiro a Sair. Então o temp vai ser o inicio da fila
    struct Node* nodeRemovido = temp->nodePosicao; // o nodeRemovido vai ser o nodePosicao do temp, ou seja, o node que tá no inicio da fila

    // Ai por penultimo a gente atualiza o inicio da fila para o valor do proximaPosicao do temp
    fila->inicio = fila->inicio->proximaPosicao; // atualiza o inicio da fila para o proximaPosicao do inicio da fila

    // Por fim, se o inicio da fila for nulo, ou seja, se a fila voltar a ficar vazia, a gente também atualiza o fim da fila para nulo
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return nodeRemovido;
}

// FUNÇÕES DO MEU DE OPÇÕES ---------------------------------------------------------------

// função opcao_1: insert node
// Para isso vamos criar uma função que irá de forma recursiva inserir e atualizar os ponteiros da arvore

struct Node* insertNode(struct Node* raiz, int valor) {

    // Primeiro coisa é verificar se a raiz é nula. Ou seja, se a arvore está vazia
    if (raiz == NULL)
    {
        return nodeNovo(valor); // se estiver vazia, a gente cria um novo node com o valor passado e retorna ele
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
// Para isso criamos os construtores da fila para armazenar os nós e ai então fazer a BFS

void bfs(struct Node* raiz) {
    // Primeira coisa é verificar se a busca não será em uma fila vazia
    if (raiz == NULL) {
        printf("fila vazia! \n");
        return;
    }

    // Beleza, não está vazia. Bora criar a fila e adicionar o node nela
    struct Fila* fila = filaNovo(); // cria a fila
    filaAdicionarNode(fila, raiz); // adiciona o node raiz na fila

    while (fila->inicio != NULL) {
        struct Node* nodeAtual = filaRemoverNode(fila);
        printf("%d ", nodeAtual->nodeValor);
        if (nodeAtual->esquerda != NULL) {
            filaAdicionarNode(fila, nodeAtual->esquerda);
        } 
        if (nodeAtual->direita != NULL) {
            filaAdicionarNode(fila, nodeAtual->direita);
        }
    }
}

// função opcao_3: verify item
void verifyItem(struct Node* raiz,int valor) {
    // Primeiro é de novo verificar se a raiz é nula.
    if (raiz == NULL) {
        printf("fila vazia!\n");
        return;
    }

    struct Node* posicaoAtual = raiz; // cria uma variável para percorrer a árvore, começando pela raiz
    
    while (posicaoAtual != NULL) {
        if (valor == posicaoAtual->nodeValor) {
            printf("Item %d encontrado na árvore.\n", valor);
            return;
        } else if (valor < posicaoAtual->nodeValor) {
            posicaoAtual = posicaoAtual->esquerda; // move para a subárvore esquerda
        } else {
            posicaoAtual = posicaoAtual->direita; // move para a subárvore direita
        }
    }

    // Se saiu do loop
    printf("Item %d não encontrado na árvore.\n", valor);
}

// função opcao_4: get MAX / MIN
// Vamos o mais a direita possivel. Então para isso vamos partir do nó raiz e ir caminhando em um while até chegar no nó mais a direita
void getMax(struct Node* raiz) {
    // Como sempre, primeiro vamos verificar se o nó raiz é nulo e se for a gente só sai da função
    if (raiz == NULL) {
        printf("Não existem nós na árvore. \n");
        return;
    }

    // Agora, se a árvore não estiver vazia, vamos a partir do nó raiz ir por meio da condicional até o nó mais a direita. Ou seja, se o nó ao final apontar para NULL é porque chegamos no nó mais a direita.
    struct Node* noMax = raiz;
    while (noMax->direita != NULL){
        noMax = noMax->direita;
    }
    printf("O valor do nó MAX é: %d\n", noMax->nodeValor);
}

// Vamos o mais a esquerda possivel. Vai ser a mesma lógica da função getMax, mas agora vamos caminhar para a esquerda
void getMin(struct Node* raiz){

    if (raiz == NULL) {
        printf("Não existem nós na árvore. \n");
        return;
    }

    struct Node* noMin = raiz;
    while (noMin->esquerda != NULL) {
        noMin = noMin->esquerda;
    }
    printf("O valor do nó MIN é: %d\n", noMin->nodeValor);
}

// FUNÇÃO PRINCIPAL ---------------------------------------------------------------

int main() {

    int opcao;
    struct Node* raiz = NULL; // inicializa a raiz como nulo

    do {
        printf("[Selecione uma Operação]\n");
        printf("1 - Insert Node\n");
        printf("2 - Breadth Search (Busca em Largura)\n");
        printf("3 - Verify item\n");
        printf("4 - Get MIN / MAX\n");
        printf("5 - Depth Search (In Order)\n");
        printf("6 - Depth Search (Pre Order)\n");
        printf("7 - Depth Search (Pos Order)\n");
        printf("8 - Depth Search (iterative Pre Order)\n");
        printf("9 - Depth Search (iterative Pos Order)\n");
        printf("10 - Depth Search (iterative In Order)\n");
        printf("11 - Exit\n");
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
                printf("Busca em Largura (BFS): ");
                bfs(raiz);
                break;
            case 3:
                printf("Digite o valor para verificar: \n");
                int valorVerificar;
                scanf("%d", &valorVerificar);
                verifyItem(raiz, valorVerificar);
                break;
            case 4:
                getMax(raiz);
                getMin(raiz);
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