#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

FILE *lista_emp;

struct Emprestimo{
    int id;
    int matricula_usuario;
    char nome[50];
    char curso[50];
    int quant_emprestimos_ativos;
};
