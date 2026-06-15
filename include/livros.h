#ifndef LIVROS_H_
#define LIVROS_H_

struct Livro
{
    int id;
    char nome[50];
    char autor[50];
    char genero[50];
    int ano;
    int quant_total;
    int quant_emprestado;
    int quant_disp;
};

// Função para pesquisar livros
void p_livros();

// Função para cadastrar livros
void c_livros();

// Função para remover livros
void r_livros();

#endif