#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 100

// 01 - DEFINIR AS STRUCTS QUE SERÃO USADAS ----------------------------------------------

// Primeira coisa é definir a struct aluno
typedef struct {
    int matricula;
    char nomeAluno[100];
} Aluno;

// Segunda coisa seria começar a pensar na tabela hash. Para isso a gente cria mais duas structs. Uma par a tabela hash e a outra para o no da lista encadeada. Ou seja, o em uma a gente guarda o Aluno e na outra a gente guarda o no da lista encadeada.

typedef struct No {
    Aluno aluno; // Aqui a gente vai guardar Aluno
    struct No* proximoNo; // Aqui a gente vai guardar o endereco do proximo no, e caso o valor encontrado em proximoNo seja NULL, siginifica que a lista encadeada cehgoua ao fim.  
} No;

typedef struct {
    No** tabela; // Aqui vamos definir uma LISTA DE PONTEIROS. Ou seja, cada posição da TabelaHash vai guardar o endereco (no*) do primeiro no daquela lista encadeada.
    int tamanho; // Aqui a gente define o tamanho da TabelaHash, e que mais para frente a gente vai estruturar um jeito de deixar esse tamanho dinâmico. Com aumentos percentuais para quando atingir o tamanho inicial/maximo corrente.
} TabelaHash;

// 02 - CRIAR A TABELA HASH ----------------------------------------------

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* novaTabelaHash = (TabelaHash*)malloc(sizeof(TabelaHash)); //  Essa primeira linhas aqui é para a gente medir o tamanho e pegar esse tamanho e alocar na memoria (via malloc)
    novaTabelaHash->tamanho = tamanho; // Aqui a gente define o tamanho da tabela hash
    novaTabelaHash->tabela = (No**)malloc(tamanho * sizeof(No*)); // Aqui a gente aloca o tamanho da tabela hash, que é o numero de posicoes vezes o tamanho de cada posicao (que é um ponteiro para No)

    for (int i = 0; i < tamanho; i++) {
        novaTabelaHash->tabela[i] = NULL; // Aqui a gente inicializa todas as posicoes da tabela hash com NULL, ou seja, sem nenhum no na lista encadeada.
    }

    return novaTabelaHash; // Aqui a gente retorna o endereco da tabela hash criada.
}

// 03 - CRIAR A FUNÇÃO DE HASH ----------------------------------------------

int funcaoHash(int matricula,  int tamanho) {
    return matricula % tamanho; // Aqui a gente retorna o resto da divisao inteira da matricula pelo tamanho da tabela hash.
}

// 04 - CRIAR AS FUNÇÕES DE INSERIR/DELETAR ALUNO ----------------------------------------------

void inserirAluno(TabelaHash* th, Aluno* aluno){
    int indice = funcaoHash(aluno->matricula, th->tamanho); // Aqui a gente vai acessar a matricula do aluno via ponteiro, bem como o tamanho da tabela hash.
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->aluno = *aluno;
    novoNo->proximoNo = th->tabela[indice];
    th->tabela[indice] = novoNo;
}

void deletarAluno(TabelaHash* th, Aluno* aluno) {
    int indice = funcaoHash(aluno->matricula, th->tamanho);
    No* atual = th->tabela[indice];
    No* anterior = NULL;

    while (atual != NULL) {
        if (atual->aluno.matricula == aluno->matricula) {
            if (anterior == NULL)
                th->tabela[indice] = atual->proximoNo;
            else
                anterior->proximoNo = atual->proximoNo;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximoNo;
    }
}

// 05 - CRIAR A FUNÇÃO DE MOSTRAR A TABELA HASH ----------------------------------------------

void displayTabelaHash(TabelaHash* th) {
    printf("\nTabela Hash:\n");
    
    for (int i = 0; i < th->tamanho; i++) {
        printf("%d", i);
        No* atual = th->tabela[i];
        while (atual != NULL) {
            printf("-> %d", atual->aluno.matricula);
            atual = atual->proximoNo;
        }
        printf("\n");
    }
}

// 06 - CRIAR A FUNÇÃO PRINCIAL ----------------------------------------------

void 