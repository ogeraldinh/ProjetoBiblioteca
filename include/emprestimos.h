#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

struct Emprestimo {
    int id_emprestimo;
    int id_livro;
    int matricula_usuario;
    int data_emp[3];
    int data_dev[3];
    int devolvido;
};

#endif