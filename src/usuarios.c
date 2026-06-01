#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

FILE *lista_u;

struct Usuario{
    int matricula;
    char nome[50];
    char curso[50];
    int quant_emprestimos_ativos;
};
