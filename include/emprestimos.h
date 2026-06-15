#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

struct Emprestimo
{
    int id;
    int matricula_usuario;
    char nome[50];
    char curso[50];
    int quant_emprestimos_ativos;
};

#endif