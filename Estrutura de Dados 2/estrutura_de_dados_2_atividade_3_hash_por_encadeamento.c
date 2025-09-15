#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 100
// #define MAX_ALUNOS 10

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

// 04 - CRIAR AS FUNÇÕES DE INSERIR/DELETAR ALUNO e a função setAluno ----------------------------------------------

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

void setAluno(Aluno* a, int matricula, const char* nomeAluno) {
    // A gente acessa a matricula via ponteiro
    a -> matricula = matricula;
    // A gente copia o nomeAluno para o campo nomeAluno da struct Aluno
    strcpy(a -> nomeAluno, nomeAluno);
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
 
// 06 - CRIAR A FUNÇÃO DE LIBERAR A MEMORIA ---------------------------------------------

void liberarMemoria(TabelaHash* th) {
    for (int i = 0; i < th->tamanho; i++) {
        No* atual = th->tabela[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximoNo;
            free(temp);
        }
    }
    free(th->tabela);
    free(th);
}

// 07 - CRIAR A MAIN ----------------------------------------------

int main() {

    // Primeiro a gente inicializa a tabela hash
    TabelaHash* th = criarTabelaHash(TAMANHO); // TAMANHO foi definido la em cima como tamanho da tabela sendo 100

    // Vou definir um menu aqui para o user poder escolher o que fazer

    int opcao; // Guardar a opcao do user

    do {
    
        printf("\nMenu:\n");
        printf("1. Inserir Aluno\n");
        printf("2. Deletar Aluno\n");
        printf("3. Mostrar Tabela Hash\n"); 
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao); // Pegar a opcao do user

        switch (opcao) {

            case 1: {
                char nomeAluno[100];
                int matricula;
                printf("Digite o nome do aluno: ");
                scanf("%s", nomeAluno);
                printf("Digite a matricula do aluno: ");
                scanf("%d", &matricula);
                
                Aluno novoAluno;
                setAluno(&novoAluno, matricula, nomeAluno);
                inserirAluno(th, &novoAluno);
                break;
            }
            case 2: {
                int matricula;
                printf("Digite a matricula do aluno a ser deletado: ");
                scanf("%d", &matricula);
                
                Aluno alunoParaDeletar;
                setAluno(&alunoParaDeletar, matricula, "");
                deletarAluno(th, &alunoParaDeletar);
                break;
            }
            case 3:
                displayTabelaHash(th);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    // Depois a gente inicializa a quantidade de alunos que o usuário podera inserir
    // Aluno alunos[MAX_ALUNOS]; // MAX_ALUNOS foi definido la em cima como 10

    // Agora a gente vai criar um for para o usuário poder inserir os alunos e as matriculas
    // for (int i = 0; i < MAX_ALUNOS; i++) {
    //    char nomeAluno[100];
    //    int matricula;
    //    printf("Digite o nome %d: ", i);
    //    scanf("%s", nomeAluno);
    //    printf("Digite a matricula %d: ", i);
    //    scanf("%d", &matricula);
        
    // A gente usa a função setAluno para setar os valores na struct Aluno
    //    setAluno(&alunos[i], matricula, nomeAluno);
    //  }

    // Agora a gente insere os alunos na tabela hash
    // for (int i = 0; i < MAX_ALUNOS; i++) {
    //    inserirAluno(th, &alunos[i]);
    //}

    // Por fim a gente libera a memoria alocada
    liberarMemoria(th);
    return 0;
}