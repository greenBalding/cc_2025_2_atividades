// N1 - Atividade 01 - biblioteca com structs.
// Aluno: MATHEUS SILVA PAINS

// Atividade: Implemente um programa que simule uma biblioteca.

// Adicionando livros
adicionarLivro(&biblioteca, "1984", "George Orwell", 1949);

// Listando acervo
listarLivros(&biblioteca);

// Operações de empéstimo
emprestarLivro(&biblioteca, 1);

// Devolvendo livro
devolverLivro(&biblioteca, 1);

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    bool disponivel;
} Livro;