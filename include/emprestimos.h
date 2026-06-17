#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

struct Emprestimo {
    int id_emprestimo;
    int id_livro;
    int matricula_usuario;

    char data_retirada[11];
    char data_prevista[11];
    char data_devolucao[11];
    
    int devolvido;
};

// Função para pesquisar empréstimos
void p_emprestimos();

// Função para cadastrar empréstimos
void c_emprestimos();

// Função de listar todos os empréstimos
void l_emprestimos();

// Função de devolução dos empréstimos
void d_emprestimos();

#endif