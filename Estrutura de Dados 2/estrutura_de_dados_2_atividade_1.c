// N1 - Atividade 01 - biblioteca com structs.
// Aluno: MATHEUS SILVA PAINS

// Atividade: Implemente um programa que simule uma biblioteca.
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_LIVROS 100

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    bool disponivel;
} Livro;

typedef struct {
    Livro livros[MAX_LIVROS]; 
    int totalLivros;
} Biblioteca;

// Função para ADICIONAR LIVRO
void adicionarLivro(Biblioteca *biblioteca, const char *titulo, const char *autor, int ano) {

    // Verificar se há espaço na biblioteca
    if (biblioteca->totalLivros >= MAX_LIVROS) {
        printf("Biblioteca cheia!\n");
        return;
    }

    // Criar um novo livro
    Livro novoLivro;

    // Preencher as informações do livro
    novoLivro.id = biblioteca->totalLivros + 1;
    strcpy(novoLivro.titulo, titulo);
    strcpy(novoLivro.autor, autor);
    novoLivro.ano = ano;
    novoLivro.disponivel = true;    

    // Adicionar o livro à biblioteca
    biblioteca->livros[biblioteca->totalLivros] = novoLivro;
    biblioteca->totalLivros++;
    
    printf("Livro adicionado com sucesso!\n", titulo);

}

// Função para LISTAR LIVROS
void listarLivros(Biblioteca *biblioteca) {

    // Verificar se há livros na biblioteca
    if (biblioteca->totalLivros == 0) {
        printf("Nenhum livro na biblioteca.\n");
        return;
    }

    // Listar todos os livros
    for (int i = 0; i < biblioteca->totalLivros; i++) {
        Livro livro = biblioteca->livros[i];
        printf("ID: %d, Titulo: %s, Autor: %s, Ano: %d, Disponivel: %s\n", livro.id, livro.titulo, livro.autor, livro.ano, livro.disponivel ? "Disponivel" : "Não Disponivel");
    }

}

// Função para EMPRESTAR LIVRO
// Verifica no booleano se o livro está disponível ou não. Usa o ID para localizar o livro.
void emprestarLivro(Biblioteca *biblioteca, int id) {

    // Verificar se o ID é válido
    if (id <= 0 || id > biblioteca->totalLivros) {
        printf("Livro não existe.\n");
        return;
    }

    // Verificar se o livro está disponível
    for (int i = 0; i < biblioteca->totalLivros; i++) {
        if (biblioteca->livros[i].id == id) {
            if (biblioteca->livros[i].disponivel) {
                biblioteca->livros[i].disponivel = false;
                printf("Livro emprestado com sucesso!\n");
            } else {
                printf("Livro não Disponivel para emprestar.\n");
            }
            return;
        }
    }
}

// Função para DEVOLVER LIVRO
void devolverLivro(Biblioteca *biblioteca, int id) {

    // Verificar se o ID é válido
    if (id <= 0 || id > biblioteca->totalLivros) {
        printf("Livro não existe.\n");
        return;
    }

    // Verificar se o livro está emprestado
    for (int i = 0; i < biblioteca->totalLivros; i++) {
        if (biblioteca->livros[i].id == id) {
            if (!biblioteca->livros[i].disponivel) {
                biblioteca->livros[i].disponivel = true;
                printf("Livro devolvido com sucesso!\n");
            } else {
                printf("Livro Disponivel para emprestar.\n");
            }
            return;
        }
    }
}

int main() {

Biblioteca biblioteca;
biblioteca.totalLivros = 0;

// Adicionando livros
adicionarLivro(&biblioteca, "1984", "George Orwell", 1949);

// Listando acervo
listarLivros(&biblioteca);

// Operações de empéstimo
emprestarLivro(&biblioteca, 1);

// Devolvendo livro
devolverLivro(&biblioteca, 1);

return 0;
}