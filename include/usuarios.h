#ifndef USUARIOS_H_
#define USUARIOS_H_

struct Usuario
{
    int matricula;
    char nome[50];
    char curso[50];
    int quant_emprestimos_ativos;
};

#endif