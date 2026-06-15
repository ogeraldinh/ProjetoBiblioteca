#include "../include/menu.h"

#include <stdio.h>
#include <locale.h>

int main()
{
    if (setlocale(LC_ALL, "pt_BR.UTF-8") == NULL)
    {
        printf("Aviso: locale pt_BR.UTF-8 nao encontrado.\n");
        printf("Caracteres acentuados podem nao ser exibidos corretamente.\n");
        setlocale(LC_ALL, "");
    }

    menuPrincipal();

    return 0;
}