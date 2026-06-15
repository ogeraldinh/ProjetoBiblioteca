#include "../include/menu.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/relatorios.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>


void menuPrincipal()
{
    FILE *logo;
    int resposta;
    char linha[50];

    logo = fopen("assets/logo.txt", "r");

    if (logo == NULL)
    {
        printf("Erro ao abrir logo.txt\n");
        return;
    }

    while (1)
    {
        printf("\n");

        rewind(logo);

        while (fgets(linha, sizeof(linha), logo))
        {
            printf("%s", linha);
        }

        printf("( 1 ) Pesquisar livros\n");
        printf("( 2 ) Cadastrar um livro\n");
        printf("( 3 ) Pesquisar usuários\n");
        printf("( 4 ) Cadastrar um usuário\n");
        printf("( 5 ) Gerar relatório\n");
        printf("( 6 ) Remover algum livro\n");
        printf("( 0 ) Encerrar o programa\n");
        printf("Selecione a opção que você deseja: ");

        if (scanf("%d", &resposta) != 1)
        {
            printf("\nResposta inválida!\n");
            limparBuffer();
            continue;
        }

        switch (resposta)
        {
        case 0:
            fclose(logo);
            printf("Encerrando...\n");
            return;

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
            printf("Gerando relatório...\n");
            break;

        case 6:
            r_livros();
            break;

        default:
            printf("Opção inválida!\n");
            limparBuffer();
        }
    }
}