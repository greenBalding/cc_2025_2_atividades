// AED: Implementação do algoritmo de árvore balanceada para um jogo
// Nome: MATHEUS SILVA PAINS - 2024.2.0028.0032-0

/*

1. Criação de um arquivo de texto com perguntas e respostas.

    1.1. O arquivo terá 20 perguntas de soma e produto, com 4 opçoes de resposta cada.

2. Carregamento das perguntas em uma árvore binária de busca balanceada (AVL). 

    2.1. Cada nó da árvore conterá:
        2.1.1. ID da pergunta (inteiro)

             "O programa deve carregar as perguntas para uma árvore AVL, utilizando um identificador numérico como chave para evitar duplicações."

        2.1.2. Texto da pergunta (string)
        2.1.3. Opções de resposta (array de strings)

             "O jogo apresenta perguntas ao jogador com opções de resposta. 
              Dependendo da resposta, a navegação ocorre dentro da árvore para a próxima questão relacionada."

        2.1.4. Próxima posição para cada opção (array de inteiros)

              "O jogador pode escolher responder corretamente e avançar, ou errar e voltar a uma questão anterior."

        2.1.5. Índice da resposta correta (inteiro)

3. Implementação das operações na árvore:

    "Compreender a estruturação, inserção, remoção e busca eficiente de dados em árvores balanceadas."

    3.1. Inserção de nós (perguntas).
    3.2. Busca de nós por ID.
    3.3. Remoção de nós por ID.
    3.4. Balanceamento da árvore após inserções e remoções.

      "O sistema deve permitir a inserção, alteração e remoção de perguntas no banco de dados, garantindo que a árvore se mantenha balanceada."

4. Implementação do jogo:

    4.1. "Ao final do jogo, o programa exibe um resumo do desempenho do jogador."
    4.2. Utilização de uma árvore AVL para gerenciar as perguntas e respostas.
    4.3. O usuário deverá ser capaz de navegar pelo jogo através da árvore.
    4.4. Será feito a leitura do arquivo .txt de acordo com a estrutura definida no item 1.
    4.5. É necessário implementar uma função que evita a duplicação de perguntas na árvore. Utilizando uma chave única. 
        4.5.1. Implementar uma hash simples para gerenciar as perguntas e evitar duplicações.
    4.6. É necessário implementar um ranking com melhores desempenhos registrados. Para isso vou criar um arquivo externo para consulta. Um arquivo log.txt

*/

// BIBLIOTECAS --------------------------------------------------------------- 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

#define MAX_TEXTO 32
#define MAX_OPCOES 4

// 1. CONSTRUTORES --------------------------------------------------------------- 

// 1.1. Struct do nó da árvore
typedef struct Node {
    int nodeValor;
    char pergunta[MAX_TEXTO];
    int nOpcoes;
    char opcoes[MAX_OPCOES][MAX_TEXTO];
    int proximaPosicao[MAX_OPCOES];
    int indiceCorreto; // 1-based
    int altura;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// 1.2. Funções para manipulação de strings
// 1.2.1. Funcao pra remover a quebra de linha e espacos finais
void removerQuebraLinha(char* s) {
    size_t l = strlen(s);
    while (l > 0 && (s[l-1] == '\n' || s[l-1] == '\r')) {
        s[l-1] = '\0';
        l--;
    }
}

// 1.2.2. Faz copia segura removendo a quebra de linha
void copiaSegura(char* dest, const char* src, size_t n) {
    strncpy(dest, src, n-1);
    dest[n-1] = '\0';
    removerQuebraLinha(dest);
}

// 1.3. Função para criar um novo nó
Node* nodeNovo(int nodeValor, const char* pergunta, int nOpcoes, char opcoes[][MAX_TEXTO], int proximaPosicao[], int indiceCorreto) {
    // vamos alocar a memoria e ver se deu certo
    Node* node = malloc(sizeof *node);
    if (node == NULL) return NULL;

    node->nodeValor = nodeValor;
    copiaSegura(node->pergunta, pergunta, MAX_TEXTO);

    // aqui a gente valida o numero de opcoes pra garantir que ta dentro do limite
    if (nOpcoes < 0) nOpcoes = 0;
    if (nOpcoes > MAX_OPCOES) nOpcoes = MAX_OPCOES;
    node->nOpcoes = nOpcoes;

    // inicializa os arrays
    for (int i = 0; i < MAX_OPCOES; i++) {
        node->opcoes[i][0] = '\0';
        node->proximaPosicao[i] = 0;
    }

    // copia so as opcoes que sao validas
    for (int i = 0; i < nOpcoes; i++) {
        copiaSegura(node->opcoes[i], opcoes[i], MAX_TEXTO);
        node->proximaPosicao[i] = proximaPosicao[i];
    }

    node->indiceCorreto = indiceCorreto;
    node->altura = 0; // um nó novo sempre começa com altura 0
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

// 2. FUNÇÕES AUXILIARES DA AVL --------------------------------------------------------------- 

// 2.1. Funcao pra pegar a altura de um no
// se o no for NULL, a gente retorna -1, que é uma convenção pro calculo do FB
int getAltura(Node* no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

// 2.2. Funcao que calcula o maximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 2.3. Funcao onde calculamos o Fator de Balanceamento de um no
// o calculo é: altura(esquerda) - altura(direita)
int getFatorBalanceamento(Node* no) {
    if (no == NULL) {
        return 0;
    }
    return getAltura(no->esquerda) - getAltura(no->direita); // Calculo do FB conforme a fórmula no slide 16.
}

// 2.4. Funcao pra atualizar a altura de um no
// a altura vai ser 1 + o maximo entre as alturas dos filhos
void atualizarAltura(Node* no) {
    if (no != NULL) {
        no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));
    }
}

// 3. ROTAÇÕES DA ÁRVORE AVL ----------------------------------------------------------------

// 3.1. Implementacao da Rotacao Simples a Direita (LL)
// usa quando: FB do no = +2 e FB do filho esquerdo >= 0
Node* rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;
    
    // realiza a rotacao
    x->direita = y;
    y->esquerda = T2;
    
    // atualiza as alturas (a ordem importa: primeiro y, depois x)
    atualizarAltura(y);
    atualizarAltura(x);
    
    // retorna a nova raiz da subarvore
    return x;
}

// 3.2. Implementacao da Rotacao Simples a Esquerda (RR)
// usa quando: FB do no = -2 e FB do filho direito <= 0
Node* rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;
    
    // realiza a rotacao
    y->esquerda = x;
    x->direita = T2;
    
    // atualiza as alturas (a ordem importa: primeiro x, depois y)
    atualizarAltura(x);
    atualizarAltura(y);
    
    // retorna a nova raiz da subarvore
    return y;
}

// 3.3. Implementacao da Rotacao Dupla a Direita (LR)
// usa quando: FB do no = +2 e FB do filho esquerdo < 0
// consiste em: Rotacao a Esquerda no filho esquerdo + Rotacao a Direita no no
Node* rotacaoDuplaDireita(Node* no) {
    // primeiro: rotacao a esquerda no filho esquerdo
    no->esquerda = rotacaoEsquerda(no->esquerda);
    
    // segundo: rotacao a direita no no
    return rotacaoDireita(no);
}

// 3.4. Implementacao da Rotacao Dupla a Esquerda (RL)
// usa quando: FB do no = -2 e FB do filho direito > 0
// consiste em: Rotacao a Direita no filho direito + Rotacao a Esquerda no no
Node* rotacaoDuplaEsquerda(Node* no) {
    // primeiro: rotacao a direita no filho direito
    no->direita = rotacaoDireita(no->direita);
    
    // segundo: rotacao a esquerda no no
    return rotacaoEsquerda(no);
}

// 4. BALANCEAMENTO DA ÁRVORE -------------------------------------------------------------

// 4.1. Funcao pra balancear um no depois de inserir/remover
// aqui a gente verifica o FB e aplica a rotacao certa se precisar
Node* balancear(Node* no) {
    if (no == NULL) {
        return NULL;
    }
    
    // atualiza a altura do no
    atualizarAltura(no);
    
    // calcula o fator de balanceamento
    int fb = getFatorBalanceamento(no);
    
    // Caso 1: desbalanceamento a Esquerda (FB = +2)
    if (fb > 1) {
        // Caso 1.1: Rotacao Simples a Direita (LL)
        if (getFatorBalanceamento(no->esquerda) >= 0) {
            return rotacaoDireita(no);
        }
        // Caso 1.2: Rotacao Dupla a Direita (LR)
        else {
            return rotacaoDuplaDireita(no);
        }
    }
    
    // Caso 2: desbalanceamento a Direita (FB = -2)
    if (fb < -1) {
        // Caso 2.1: Rotacao Simples a Esquerda (RR)
        if (getFatorBalanceamento(no->direita) <= 0) {
            return rotacaoEsquerda(no);
        }
        // Caso 2.2: Rotacao Dupla a Esquerda (RL)
        else {
            return rotacaoDuplaEsquerda(no);
        }
    }
    
    // o no ta balanceado, entao a gente retorna sem alteracoes
    return no;
}

// 5. OPERAÇÕES NA ÁRVORE (INSERIR, BUSCAR, REMOVER) ----------------------------------

// 5.1. Inserir nó
Node* inserirNo(Node* raiz, Node* novo) {
    if (raiz == NULL) return novo;
    if (novo->nodeValor < raiz->nodeValor) raiz->esquerda = inserirNo(raiz->esquerda, novo);
    else if (novo->nodeValor > raiz->nodeValor) raiz->direita = inserirNo(raiz->direita, novo);
    else {
        // encontramos um duplicado: nesse caso, vamos substituir os dados
        copiaSegura(raiz->pergunta, novo->pergunta, MAX_TEXTO);
        raiz->nOpcoes = novo->nOpcoes;
        for (int i = 0; i < raiz->nOpcoes; i++) {
            copiaSegura(raiz->opcoes[i], novo->opcoes[i], MAX_TEXTO);
            raiz->proximaPosicao[i] = novo->proximaPosicao[i];
        }
        raiz->indiceCorreto = novo->indiceCorreto;
        free(novo); // libera o no novo que nao sera usado
        return raiz;
    }
    return balancear(raiz);
}

// 5.2. Buscar nó
Node* buscarNo(Node* raiz, int nodeValor) {
    Node* atual = raiz;
    while (atual != NULL) {
        if (nodeValor == atual->nodeValor) return atual;
        else if (nodeValor < atual->nodeValor) atual = atual->esquerda;
        else atual = atual->direita;
    }
    return NULL;
}

// 5.3. Encontrar nó de menor valor
Node* noMenorValor(Node* node) {
    Node* atual = node;
    while (atual && atual->esquerda != NULL) atual = atual->esquerda;
    return atual;
}

// 5.4. Remover nó
Node* removerNo(Node* raiz, int nodeValor, int* removed) {
    if (raiz == NULL) return raiz;
    if (nodeValor < raiz->nodeValor) raiz->esquerda = removerNo(raiz->esquerda, nodeValor, removed);
    else if (nodeValor > raiz->nodeValor) raiz->direita = removerNo(raiz->direita, nodeValor, removed);
    else {
        // encontramos o nó
        *removed = 1;
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            Node* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            Node* temp = noMenorValor(raiz->direita);
            raiz->nodeValor = temp->nodeValor;
            copiaSegura(raiz->pergunta, temp->pergunta, MAX_TEXTO);
            raiz->nOpcoes = temp->nOpcoes;
            for (int i = 0; i < raiz->nOpcoes; i++) {
                copiaSegura(raiz->opcoes[i], temp->opcoes[i], MAX_TEXTO);
                raiz->proximaPosicao[i] = temp->proximaPosicao[i];
            }
            raiz->indiceCorreto = temp->indiceCorreto;
            raiz->direita = removerNo(raiz->direita, temp->nodeValor, removed);
        }
    }
    if (raiz == NULL) return raiz;
    return balancear(raiz);
}

// 5.5. Atualiza as referencias que apontam para um ID removido, trocando por 0
void atualizarReferencias(Node* raiz, int nodeValorRemovido) {
    if (raiz == NULL) return;
    for (int i = 0; i < raiz->nOpcoes; i++) {
        if (raiz->proximaPosicao[i] == nodeValorRemovido) raiz->proximaPosicao[i] = 0;
    }
    atualizarReferencias(raiz->esquerda, nodeValorRemovido);
    atualizarReferencias(raiz->direita, nodeValorRemovido);
}

// 5.6. Limpa a arvore completamente
void clearTree(Node* raiz) {
    if (raiz != NULL) {
        clearTree(raiz->esquerda);
        clearTree(raiz->direita);
        free(raiz);
    }
}

// 6. LEITURA E ESCRITA DO ARQUIVO DE PERGUNTAS ------------------------

// 6.1. Le um bloco e retorna 1 se leu a questao, ou 0 se deu erro/EOF
int lerBloco(FILE* f, int* nodeValor_out, char* pergunta_out, int* nOpcoes_out, char opcoes_out[][MAX_TEXTO], int proximaPosicao_out[], int* indiceCorreto_out) {
    char linha[1024];
    // vamos ler o ID
    while (fgets(linha, sizeof(linha), f)) {
        removerQuebraLinha(linha);
        // pula as linhas que estiverem vazias
        char* p = linha;
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0') continue;
        *nodeValor_out = atoi(p);
        break;
    }
    if (feof(f)) return 0;
    if (ferror(f)) return 0;
    // le a Pergunta
    if (!fgets(linha, sizeof(linha), f)) return 0;
    removerQuebraLinha(linha);
    copiaSegura(pergunta_out, linha, MAX_TEXTO);
    // le o numero de opcoes
    if (!fgets(linha, sizeof(linha), f)) return 0;
    removerQuebraLinha(linha);
    *nOpcoes_out = atoi(linha);
    if (*nOpcoes_out < 0 || *nOpcoes_out > MAX_OPCOES) *nOpcoes_out = 0;
    // le as opcoes
    for (int i = 0; i < *nOpcoes_out; i++) {
        if (!fgets(linha, sizeof(linha), f)) return 0;
        removerQuebraLinha(linha);
        char* sep = strchr(linha, ';');
        if (sep) {
            *sep = '\0';
            copiaSegura(opcoes_out[i], linha, MAX_TEXTO);
            proximaPosicao_out[i] = atoi(sep + 1);
        } else {
            copiaSegura(opcoes_out[i], linha, MAX_TEXTO);
            proximaPosicao_out[i] = 0;
        }
    }
    // le o indice correto
    if (!fgets(linha, sizeof(linha), f)) return 0;
    removerQuebraLinha(linha);
    *indiceCorreto_out = atoi(linha);
    return 1;
}

// 6.2. Carregar arquivo
Node* carregarArquivo(const char* caminho) {
    FILE* f = fopen(caminho, "r");
    if (!f) return NULL;
    Node* raiz = NULL;
    int nodeValorLocal, nOpcoesLocal, indiceCorretoLocal;
    char pergunta[MAX_TEXTO];
    char opcoesLocal[MAX_OPCOES][MAX_TEXTO];
    int proximaLocal[MAX_OPCOES];
    while (lerBloco(f, &nodeValorLocal, pergunta, &nOpcoesLocal, opcoesLocal, proximaLocal, &indiceCorretoLocal)) {
        Node* novo = nodeNovo(nodeValorLocal, pergunta, nOpcoesLocal, opcoesLocal, proximaLocal, indiceCorretoLocal);
        // mantem a ordem definida em perguntas.txt (sem embaralhar)
        raiz = inserirNo(raiz, novo);
    }
    fclose(f);
    return raiz;
}

// 6.3. Salva em ordem crescente (in-order)
void salvarInOrder(Node* raiz, FILE* f) {
    if (!raiz) return;
    salvarInOrder(raiz->esquerda, f);
    fprintf(f, "%d\n", raiz->nodeValor);
    fprintf(f, "%s\n", raiz->pergunta);
    fprintf(f, "%d\n", raiz->nOpcoes);
    for (int i = 0; i < raiz->nOpcoes; i++) {
        fprintf(f, "%s;%d\n", raiz->opcoes[i], raiz->proximaPosicao[i]);
    }
    fprintf(f, "%d\n", raiz->indiceCorreto);
    salvarInOrder(raiz->direita, f);
}

// 6.4. Salvar arquivo
int salvarArquivo(Node* raiz, const char* caminho) {
    FILE* f = fopen(caminho, "w");
    if (!f) return 0;
    salvarInOrder(raiz, f);
    fclose(f);
    return 1;
}

// 6.5. Imprime os IDs em ordem (InOrder)
void imprimirInOrder(Node* r) {
    if (!r) return;
    imprimirInOrder(r->esquerda);
    printf("%d ", r->nodeValor);
    imprimirInOrder(r->direita);
}

// 7. FUNÇÕES DE JOGO E RANKING --------------------------------------- 

// 7.1. Encontrar o início do jogo (nó com menor ID)
Node* encontrarInicio(Node* raiz) {
    return noMenorValor(raiz);
}

// 7.2. Pilha simples de historico de ids
// 7.2.1. Struct da Pilha
typedef struct {
    int dados[1024];
    int topo;
} Pilha;

// 7.2.2. Inicializar a pilha
void pilha_inicializar(Pilha* p) { p->topo = -1; }
// 7.2.3. Verificar se a pilha está vazia
int pilha_vazia(Pilha* p) { return p->topo == -1; }
// 7.2.4. Empilhar (push)
void pilha_empilhar(Pilha* p, int v) { if (p->topo < 1023) p->dados[++p->topo] = v; }
// 7.2.5. Desempilhar (pop)
int pilha_desempilhar(Pilha* p) { if (p->topo >= 0) return p->dados[p->topo--]; return 0; }

// 7.3. Jogar: loop de interacao com o jogador
void jogar(Node* raiz) {
    if (raiz == NULL) {
        printf("Árvore vazia. Carregue um arquivo antes de jogar.\n");
        return;
    }
    Node* atual = encontrarInicio(raiz);
    Pilha hist;
    pilha_inicializar(&hist);
    int score = 0;
    char buf[32];
    while (atual != NULL) {
        printf("\nPergunta (ID=%d): %s\n", atual->nodeValor, atual->pergunta);
        for (int i = 0; i < atual->nOpcoes; i++) {
            printf("%d) %s\n", i+1, atual->opcoes[i]);
        }
        printf("Escolha (q para sair): ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        removerQuebraLinha(buf);
        if (strcmp(buf, "q") == 0) break;
        int escolha = atoi(buf);
        if (escolha < 1 || escolha > atual->nOpcoes) {
            printf("Escolha inválida. Tente novamente.\n");
            continue;
        }
        // verifica se a resposta ta correta
        if (escolha == atual->indiceCorreto) {
            printf("Correto!\n");
            score++;
            int prox = atual->proximaPosicao[escolha-1];
            if (prox == 0) {
                printf("Fim do caminho.\n");
                break;
            }
            pilha_empilhar(&hist, atual->nodeValor);
            atual = buscarNo(raiz, prox);
            if (atual == NULL) {
                printf("Próxima questão (ID=%d) não encontrada. Fim.\n", prox);
                break;
            }
        } else {
            printf("Errado. Voltando à questão anterior (se existir).\n");
            if (!pilha_vazia(&hist)) {
                int prev = pilha_desempilhar(&hist);
                    atual = buscarNo(raiz, prev);
                if (atual == NULL) {
                    printf("Questão anterior removida. Fim de jogo.\n");
                    break;
                }
            } else {
                printf("Sem questão anterior. Fim de jogo.\n");
                break;
            }
        }
    }
    printf("\nResumo: Pontuação = %d\n", score);
    // vamos salvar o ranking
    printf("Digite seu nome para o ranking (ou deixe em branco para não salvar): ");
    char nome[128];
    if (!fgets(nome, sizeof(nome), stdin)) return;
    removerQuebraLinha(nome);
    if (strlen(nome) > 0) {
        FILE* rf = fopen("ranking.txt", "a");
        if (rf) {
            time_t t = time(NULL);
            fprintf(rf, "%s;%d;%ld\n", nome, score, (long)t);
            fclose(rf);
            printf("Pontuação registrada.\n");
        } else {
            printf("Erro ao gravar ranking.\n");
        }
    }
}

// 7.4. Mostrar Ranking: lemos o ranking.txt, ordenamos por score e exibimos
void mostrarRanking() {
    FILE* f = fopen("ranking.txt", "r");
    if (!f) { printf("Nenhum ranking registrado.\n"); return; }
    typedef struct { char nome[128]; int score; long t; } Entry;
    Entry lista[1024]; int n = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        removerQuebraLinha(linha);
        char* p1 = strchr(linha, ';');
        if (!p1) continue;
        *p1 = '\0';
        copiaSegura(lista[n].nome, linha, 128);
        char* p2 = p1 + 1;
        char* p3 = strchr(p2, ';');
        if (!p3) continue;
        *p3 = '\0';
        lista[n].score = atoi(p2);
        lista[n].t = atol(p3+1);
        n++; if (n >= 1024) break;
    }
    fclose(f);
    // ordenamos de forma decrescente
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (lista[j].score > lista[i].score) {
                Entry tmp = lista[i]; lista[i] = lista[j]; lista[j] = tmp;
            }
        }
    }
    printf("\n--- Ranking ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s - %d\n", i+1, lista[i].nome, lista[i].score);
    }
}

// 8. FUNÇÕES DO MENU -----------------------------------------------------------

// 8.1. Inserir questão pelo prompt
void inserirQuestaoMenu(Node** raiz) {
    char linha[1024];
    
    // vamos pedir o ID da questao
    printf("Digite ID da questão: "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    int nodeValor = atoi(linha);
    
    // vamos pedir o texto da pergunta
    printf("Digite a pergunta (uma linha): "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    removerQuebraLinha(linha);
    char pergunta[MAX_TEXTO]; 
    copiaSegura(pergunta, linha, MAX_TEXTO);
    
    // vamos pedir o numero de opcoes
    printf("Número de opções (max %d): ", MAX_OPCOES); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    int nOpcoes = atoi(linha); 
    if (nOpcoes < 1) nOpcoes = 1; 
    if (nOpcoes > MAX_OPCOES) nOpcoes = MAX_OPCOES;
    
    char opcoesLocal[MAX_OPCOES][MAX_TEXTO]; 
    int proximaLocal[MAX_OPCOES];
    
    // vamos pedir cada opcao e seu proximo ID
    for (int i = 0; i < nOpcoes; i++) {
        printf("Texto da opção %d: ", i+1); 
        if (!fgets(linha, sizeof(linha), stdin)) return; 
        removerQuebraLinha(linha); 
        copiaSegura(opcoesLocal[i], linha, MAX_TEXTO);
        
        printf("Next ID da opção %d (0 para fim): ", i+1); 
        if (!fgets(linha, sizeof(linha), stdin)) return; 
        proximaLocal[i] = atoi(linha);
    }
    
    // vamos pedir o indice da resposta correta
    printf("Índice da opção correta (1-based): "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    int indiceCorreto = atoi(linha);
    
    // vamos criar o novo no e inserir na arvore
    Node* novo = nodeNovo(nodeValor, pergunta, nOpcoes, opcoesLocal, proximaLocal, indiceCorreto);
    *raiz = inserirNo(*raiz, novo);
    
    printf("Questão inserida/atualizada.\n");
}

// 8.2. Editar os campos de uma questão existente
void modificarQuestao(Node* raiz) {
    char linha[512];
    
    // vamos pedir o ID da questao a ser modificada
    printf("Digite ID da questão a modificar: "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    int nodeValor = atoi(linha);
    
    // vamos buscar a questao na arvore
    Node* quest = buscarNo(raiz, nodeValor);
    if (!quest) { 
        printf("Questão não encontrada.\n"); 
        return; 
    }
    
    // vamos mostrar a pergunta atual e pedir a nova
    printf("Questão atual: %s\n", quest->pergunta);
    printf("Nova pergunta (enter para manter): "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    removerQuebraLinha(linha); 
    if (strlen(linha) > 0) copiaSegura(quest->pergunta, linha, MAX_TEXTO);
    
    // vamos mostrar o numero de opcoes atual e pedir o novo
    printf("Número de opções atual: %d\n", quest->nOpcoes);
    printf("Novo número de opções (0 para manter): "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    int novo_n = atoi(linha); 
    if (novo_n <= 0) novo_n = quest->nOpcoes; 
    if (novo_n > MAX_OPCOES) novo_n = MAX_OPCOES;
    
    // vamos iterar sobre as opcoes pra atualizar texto e proximo ID
    for (int i = 0; i < novo_n; i++) {
        printf("Opção %d atual: %s\n", i+1, quest->opcoes[i]);
        printf("Nova opção (enter para manter): "); 
        if (!fgets(linha, sizeof(linha), stdin)) return; 
        removerQuebraLinha(linha); 
        if (strlen(linha) > 0) copiaSegura(quest->opcoes[i], linha, MAX_TEXTO);
        
        printf("Next ID atual: %d\n", quest->proximaPosicao[i]);
        printf("Novo Next ID (enter para manter): "); 
        if (!fgets(linha, sizeof(linha), stdin)) return; 
        removerQuebraLinha(linha); 
        if (strlen(linha) > 0) quest->proximaPosicao[i] = atoi(linha);
    }
    quest->nOpcoes = novo_n;
    
    // vamos atualizar o indice da resposta correta
    printf("Índice correto atual: %d\n", quest->indiceCorreto);
    printf("Novo índice correto (0 para manter): "); 
    if (!fgets(linha, sizeof(linha), stdin)) return; 
    int newc = atoi(linha); 
    if (newc > 0) quest->indiceCorreto = newc;
    
    printf("Questão modificada.\n");
}

// 9. FUNÇÃO PRINCIPAL ---------------------------------------------------------------

int main() {
    Node* raiz = NULL;
    char caminho[512] = "perguntas.txt"; // arquivo padrao
    int opcao;
    char buf[128];

    do {
        printf("[Selecione uma Operação]\n");
        printf("1 - Carregar arquivo (%s)\n", caminho);
        printf("2 - Salvar arquivo (%s)\n", caminho);
        printf("3 - Jogar\n");
        printf("4 - Inserir questão\n");
        printf("5 - Modificar questão\n");
        printf("6 - Remover questão\n");
        printf("7 - Mostrar (InOrder IDs)\n");
        printf("8 - Ranking\n");
        printf("9 - Alterar arquivo de perguntas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        
        if (!fgets(buf, sizeof(buf), stdin)) break;
        opcao = atoi(buf);

        switch (opcao) {
            case 1:
                printf("Carregando %s ...\n", caminho);
                clearTree(raiz); 
                raiz = carregarArquivo(caminho);
                if (raiz) printf("Arquivo carregado com sucesso.\n"); 
                else printf("Arquivo não encontrado ou vazio.\n");
                break;
            case 2:
                if (salvarArquivo(raiz, caminho)) printf("Arquivo salvo.\n"); 
                else printf("Erro ao salvar.\n");
                break;
            case 3:
                jogar(raiz);
                break;
            case 4:
                inserirQuestaoMenu(&raiz);
                break;
            case 5:
                modificarQuestao(raiz);
                break;
            case 6:
                printf("ID a remover: "); 
                if (!fgets(buf, sizeof(buf), stdin)) break; 
                int idr = atoi(buf);
                int removed = 0;
                raiz = removerNo(raiz, idr, &removed);
                if (removed) {
                    atualizarReferencias(raiz, idr);
                    printf("Questão removida e referências atualizadas.\n");
                } else printf("ID não encontrado.\n");
                break;
            case 7:
                printf("IDs em ordem (InOrder): ");
                imprimirInOrder(raiz);
                printf("\n");
                break;
            case 8:
                mostrarRanking();
                break;
            case 9:
                printf("Digite novo caminho do arquivo: "); 
                if (!fgets(caminho, sizeof(caminho), stdin)) break; 
                removerQuebraLinha(caminho);
                break;
            case 0:
                printf("Saindo...\n");
                clearTree(raiz);
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
