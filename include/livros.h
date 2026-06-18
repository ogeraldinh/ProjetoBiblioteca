#ifndef LIVROS_H_
#define LIVROS_H_

// Estrutura de um Livro (atributos)
struct Livro {
    int id;
    char nome[50];
    char autor[50];
    char genero[50];
    int ano;
    int quant_total;
    int quant_emprestado;
    int quant_disp;
    int total_emprestimos;
};

// Função para cadastrar livros
void c_livros();

// Função para pesquisar livros
void p_livros();

// Função para remover livros
void r_livros();

// Função de listar todos os livros
void l_livros();

// Função de atualizar dados dos livros
void a_livros();

// Função para informar que o livro está emprestado para tais usuários
void e_livros();

#endif