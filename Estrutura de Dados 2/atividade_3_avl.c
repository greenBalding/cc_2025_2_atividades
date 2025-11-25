// N2 - Atividade 03 - Árvores AVL

// Nome: MATHEUS SILVA PAINS - 2024.2.0028.0032-0

/* 

Instruções: Implementar as funções de uma árvore AVL conforme o seguinte menu:

>>> N2 Atividade 03 <<<
- Insert Node
- Breadth Search (Busca em Largura)
- Verify item
- Clear Tree
- Depth Search (In Order)
- Depth Search (Pre Order)
- Depth Search (Pos Order)
- Exit

*/

// BIBLIOTECAS ---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

// CONSTRUTORES ---------------------------------------------------------------

// 1.1.1. vamos criar a struct pro node
typedef struct Node {
    int nodeValor;
    int altura;  // Diferença do construtor anterior (1). Altura que será usada para fazer o calculo do FB para saber se será necessário balancear ou não.
    struct Node* esquerda;
    struct Node* direita;
} Node;

// 1.1.2. vamos criar a funcao para criar um novo node
struct Node* nodeNovo(int valor) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); // vamo mallocar a memoria pro node

    node->nodeValor = valor; // ai aqui a gente atribui o valor para o node. Na verdade o usuário vai passar o valor na hora de selecionar a opção 1
    node->altura = 0; // Diferença do construtor anterior (2). Inicializa a altura como 0 para um novo nó, dado que ele não tem filhos ainda.
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

// FUNÇÕES AUXILIARES AVL ---------------------------------------------------------------

// 2.1. Função para obter a altura de um nó
// Se o nó for NULL, retorna -1 (convenção para cálculo do FB)
int getAltura(struct Node* no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

// 2.2. Função para calcular o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 2.3. Função para calcular o Fator de Balanceamento de um nó
// FB = altura(esquerda) - altura(direita)
int getFatorBalanceamento(struct Node* no) {
    if (no == NULL) {
        return 0;
    }
    return getAltura(no->esquerda) - getAltura(no->direita); // Calculo do FB conforme a fórmula no slide 16.
}

// 2.4. Função para atualizar a altura de um nó
// A altura é 1 + máximo entre as alturas dos filhos
void atualizarAltura(struct Node* no) {
    if (no != NULL) {
        no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));
    }
}

// 3.1. Rotação Simples à Direita (LL)
// Usada quando: FB do nó = +2 e FB do filho esquerdo >= 0
struct Node* rotacaoDireita(struct Node* y) {
    struct Node* x = y->esquerda;
    struct Node* T2 = x->direita;
    
    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;
    
    // Atualiza as alturas (ordem importa: primeiro y, depois x)
    atualizarAltura(y);
    atualizarAltura(x);
    
    // Retorna a nova raiz da subárvore
    return x;
}

// 3.2. Rotação Simples à Esquerda (RR)
// Usada quando: FB do nó = -2 e FB do filho direito <= 0
struct Node* rotacaoEsquerda(struct Node* x) {
    struct Node* y = x->direita;
    struct Node* T2 = y->esquerda;
    
    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;
    
    // Atualiza as alturas (ordem importa: primeiro x, depois y)
    atualizarAltura(x);
    atualizarAltura(y);
    
    // Retorna a nova raiz da subárvore
    return y;
}

// 3.3. Rotação Dupla à Direita (LR)
// Usada quando: FB do nó = +2 e FB do filho esquerdo < 0
// Consiste em: Rotação à Esquerda no filho esquerdo + Rotação à Direita no nó
struct Node* rotacaoDuplaDireita(struct Node* no) {
    // Primeiro: rotação à esquerda no filho esquerdo
    no->esquerda = rotacaoEsquerda(no->esquerda);
    
    // Segundo: rotação à direita no nó
    return rotacaoDireita(no);
}

// 3.4. Rotação Dupla à Esquerda (RL)
// Usada quando: FB do nó = -2 e FB do filho direito > 0
// Consiste em: Rotação à Direita no filho direito + Rotação à Esquerda no nó
struct Node* rotacaoDuplaEsquerda(struct Node* no) {
    // Primeiro: rotação à direita no filho direito
    no->direita = rotacaoDireita(no->direita);
    
    // Segundo: rotação à esquerda no nó
    return rotacaoEsquerda(no);
}

// 4.1. Função para balancear um nó após inserção
// Verifica o FB e aplica a rotação apropriada se necessário
struct Node* balancear(struct Node* no) {
    if (no == NULL) {
        return NULL;
    }
    
    // Atualiza a altura do nó
    atualizarAltura(no);
    
    // Calcula o fator de balanceamento
    int fb = getFatorBalanceamento(no);
    
    // Caso 1: Desbalanceamento à Esquerda (FB = +2)
    if (fb > 1) {
        // Caso 1a: Rotação Simples à Direita (LL)
        if (getFatorBalanceamento(no->esquerda) >= 0) {
            return rotacaoDireita(no);
        }
        // Caso 1b: Rotação Dupla à Direita (LR)
        else {
            return rotacaoDuplaDireita(no);
        }
    }
    
    // Caso 2: Desbalanceamento à Direita (FB = -2)
    if (fb < -1) {
        // Caso 2a: Rotação Simples à Esquerda (RR)
        if (getFatorBalanceamento(no->direita) <= 0) {
            return rotacaoEsquerda(no);
        }
        // Caso 2b: Rotação Dupla à Esquerda (RL)
        else {
            return rotacaoDuplaEsquerda(no);
        }
    }
    
    // Nó está balanceado, retorna sem alterações
    return no;
}

// FUNÇÕES DO MEU DE OPÇÕES ---------------------------------------------------------------

// função opcao_1: insert node
// Para isso vamos criar uma função que irá de forma recursiva inserir e atualizar os ponteiros da arvore (com balanceamento AVL)
struct Node* insertNode(struct Node* raiz, int valor) {

    // Primeiro coisa é verificar se a raiz é nula. Ou seja, se a arvore está vazia
    if (raiz == NULL) 
    {
        return nodeNovo(valor); // se estiver vazia, a gente cria um novo node com o valor passado e retorna ele
    }
    
    // Ai caso a arvore não esteja vazia, a gente pode começar a inserir os valores com base no valor raiz e fazer as comparações
    if (valor < raiz->nodeValor) 
    {
        raiz->esquerda = insertNode(raiz->esquerda, valor); // se o valor for menor que o valor da raiz, a gente insere ele na subarvore esquerda
    } else if (valor > raiz->nodeValor) {
        raiz->direita = insertNode(raiz->direita, valor); // se o valor for maior que o valor da raiz, a gente insere ele na subarvore direita
    }

    return balancear(raiz); // Diferença do código anterior (3). A diferença aqui é que inves de retornar a raiz diretamente, aqui a gente retorna a raiz balanceada. DADO QUE, a gente precisa garantir que a árvore permaneça balanceada após cada inserção.
}

// função opcao_2: breadth search (BFS - Busca em Largura)
// Usando a implementação de fila (Fila, nodeFila, filaNovo, filaAdicionarNode, filaRemoverNode)

void bfs(struct Node* raiz) {
    // Primeira coisa é verificar se a busca não será em uma fila vazia
    if (raiz == NULL) {
        printf("fila vazia!\n");
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
void verifyItem(struct Node* raiz, int valor) {
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

// função opcao_4: clear tree
// função que entra no lugar de MAX/MIN do código anterior
void clearTree(struct Node* raiz) {
    if (raiz != NULL) {
        clearTree(raiz->esquerda);
        clearTree(raiz->direita);
        free(raiz);
    }
}

// FUNÇÕES DE PROFUNDIDADE (DEPTH SEARCH) ---------------------------------------------------------------

// função opcao_5: Depth Search (In Order) - Recursiva
// Primeiro a gente percorre a sub-árvore esquerda, depois visita a raiz, e depois a sub-árvore direita
void depthSearchInOrderRecursiva(struct Node* raiz) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // se estiver vazia, a gente sai da função
    }
    
    depthSearchInOrderRecursiva(raiz->esquerda); // percorre a sub-árvore esquerda
    printf("%d ", raiz->nodeValor); // visita a raiz
    depthSearchInOrderRecursiva(raiz->direita); // percorre a sub-árvore direita
}

// função opcao_6: Depth Search (Pre Order) - Recursiva
// Primeiro a gente visita a raiz, depois percorre a sub-árvore esquerda, e depois a sub-árvore direita
void depthSearchPreOrderRecursiva(struct Node* raiz) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // se estiver vazia, a gente sai da função
    }
    
    printf("%d ", raiz->nodeValor); // visita a raiz
    depthSearchPreOrderRecursiva(raiz->esquerda); // percorre a sub-árvore esquerda
    depthSearchPreOrderRecursiva(raiz->direita); // percorre a sub-árvore direita
}

// função opcao_7: Depth Search (Pos Order) - Recursiva
// Primeiro a gente percorre a sub-árvore esquerda, depois a sub-árvore direita, e por último visita a raiz
void depthSearchPosOrderRecursiva(struct Node* raiz) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // se estiver vazia, a gente sai da função
    }
    
    depthSearchPosOrderRecursiva(raiz->esquerda); // percorre a sub-árvore esquerda
    depthSearchPosOrderRecursiva(raiz->direita); // percorre a sub-árvore direita
    printf("%d ", raiz->nodeValor); // visita a raiz
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
        printf("4 - Clear Tree\n");
        printf("5 - Depth Search (In Order)\n");
        printf("6 - Depth Search (Pre Order)\n");
        printf("7 - Depth Search (Pos Order)\n");
        printf("8 - Exit\n");
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
                clearTree(raiz);
                raiz = NULL;
                printf("Árvore limpa com sucesso!\n");
                break;
            case 5:
                printf("Depth Search (In Order): ");
                if (raiz == NULL) {
                    printf("Árvore vazia!");
                } else {
                    depthSearchInOrderRecursiva(raiz);
                }
                printf("\n");
                break;
            case 6:
                printf("Depth Search (Pre Order): ");
                if (raiz == NULL) {
                    printf("Árvore vazia!");
                } else {
                    depthSearchPreOrderRecursiva(raiz);
                }
                printf("\n");
                break;
            case 7:
                printf("Depth Search (Pos Order): ");
                if (raiz == NULL) {
                    printf("Árvore vazia!");
                } else {
                    depthSearchPosOrderRecursiva(raiz);
                }
                printf("\n");
                break;
            case 8:
                printf("Saindo...\n");
                clearTree(raiz);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (opcao != 8);
    return 0;
}