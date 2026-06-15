#include "../include/menu.h"

#include <stdio.h>
#include <locale.h>

int main()
{
    if (setlocale(LC_ALL, "pt_BR.UTF-8") == NULL)
    {
        printf("Aviso: locale pt_BR.UTF-8 nao encontrado.\n");
    }

    menuPrincipal();

    return 0;
}