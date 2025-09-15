#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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