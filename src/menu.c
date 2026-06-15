#include "../include/menu.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/relatorios.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>


void menuPrincipal()
{
    limparTela();

    FILE *title;
    int resposta;
    char linha[50];

    title = fopen("assets/biblioteca.txt", "r");

    if (title == NULL)
    {
        printf("Erro ao abrir biblioteca.txt\n");
        return;
    }

    while (1)
    {
        printf("\n");

        rewind(title);

        while (fgets(linha, sizeof(linha), title))
        {
            printf("%s", linha);
        }
        printf("------------------------------------------------------");
        printf("\n");
        printf("( 1 ) Gerenciar livros.\n");
        printf("( 2 ) Gerenciar usuários.\n");
        printf("( 3 ) Realizar empréstimo.\n");
        printf("( 4 ) Registrar devolução.\n");
        printf("( 5 ) Relatórios.\n");
        printf("( 0 ) Encerrar o programa.\n");
        printf("\n");
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
            fclose(title);
            printf("Encerrando...\n");
            return;

        case 1:
            limparTela();
            menuLivros();
            break;

        case 2:
            limparTela();
            menuUsuarios();
            break;

        case 3:
            limparTela();
            menuEmprestimos();
            break;

        case 4:
            limparTela();
            menuDevolucoes();
            break;

        case 5:
            limparTela();
            menuRelatorios();
            break;

        default:
            printf("Opção inválida!\n");
            limparBuffer();
        }
    }
}
void menuLivros(){

    FILE *title;
    int resposta;
    char linha[50];

    title = fopen("assets/livros.txt", "r");

    if (title == NULL)
    {
        printf("Erro ao abrir livros.txt\n");
        return;
    }

    while (1)
    {
        printf("\n");

        rewind(title);

        while (fgets(linha, sizeof(linha), title))
        {
            printf("%s", linha);
        }
        printf("---------------------------------");
        printf("\n");
        printf("( 1 ) Pesquisar livros.\n");
        printf("( 2 ) Cadastrar um livro.\n");
        printf("( 3 ) Remover algum livro.\n");
        printf("( 0 ) Retornar.\n");
        printf("\n");

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
            fclose(title);
            limparTela();
            return;

        case 1:
            limparTela();
            p_livros();
            break;

        case 2:
            limparTela();
            c_livros();
            break;

        case 3:
            limparTela();
            r_livros();
            break;

        default:
            printf("Opção inválida!\n");
            limparBuffer();
        }
    }
}
void menuUsuarios(){}
void menuEmprestimos(){}
void menuDevolucoes(){}
void menuRelatorios(){}