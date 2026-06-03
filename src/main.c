#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include "../include/menu.h"

int main()
{
    FILE *logo;
    int resposta;
    char linha[50];

    setlocale(LC_ALL, "pt_BR.UTF-8");

    logo = fopen("../assets/logo.txt", "r");

    if (logo == NULL)
    {
        printf("Erro ao abrir logo.txt\n");
        return 1;
    }

    while (1)
    {
        printf("\n");
    
        rewind(logo);

        while (fgets(linha, sizeof(linha), logo))
        {
            printf("%s", linha);
        }

        printf("( 1 ) Pesquisar livros \n");
        printf("( 2 ) Cadastrar um livro \n");
        printf("( 3 ) Pesquisar usuários \n");
        printf("( 4 ) Cadastrar um usuário \n");
        printf("( 5 ) Gerar relatório \n");
        printf("( 0 ) Encerrar o programa \n");
        printf("Selecione a opção que você deseja: ");

        if (!scanf("%d", &resposta))
        {
            printf("\nResposta inválida! Por favor, digite uma das opções.\n");
            getchar();
            continue;
        }

        switch (resposta)
        {
        case 0:
            fclose(logo);
            printf("Encerrando...");
            printf("\n");
            return 0;
        case 1:
            p_livros();
            break;
        case 2:
            c_livros();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("\n");
            printf("Gerando relatório...\n");
            printf("\n");
            break;
        default:
            printf("\nResposta inválida! Por favor, digite uma das opções.\n");
            getchar();
            break;
        }
    }

    return 0;
}