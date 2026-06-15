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

    int resposta;

    while (1)
    {
        exibirTitulo("assets/biblioteca.txt");
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
            erroEntrada("Opção inválida!");
            continue;
        }

        switch (resposta)
        {
        case 0:
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
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

void menuLivros(){
    int resposta;

    while (1)
    {
        exibirTitulo("assets/livros.txt");
        printf("\n");
        printf("( 1 ) Listar todos os livros.\n");
        printf("( 2 ) Pesquisar livros.\n");
        printf("( 3 ) Cadastrar um livro.\n");
        printf("( 4 ) Remover algum livro.\n");
        printf("( 5 ) Atualizar algum dado de um livro.\n");
        /* Informar, para um dado livro, para quais usuários ele está emprestado no momento 
        (caso não haja, informar que o livro não possui empréstimos);*/
        printf("( 6 ) Emprestimos de livros.\n");
        printf("( 0 ) Retornar.\n");
        printf("\n");

        printf("Selecione a opção que você deseja: ");

        if (scanf("%d", &resposta) != 1)
        {
            erroEntrada("Opção inválida!");
            continue;
        }

        switch (resposta)
        {
        case 0:
            limparTela();
            return;

        case 1:
            limparTela();
            l_livros();
            break;

        case 2:
            limparTela();
            p_livros();
            break;

        case 3:
            limparTela();
            c_livros();
            break;

        case 4:
            limparTela();
            r_livros();
            break;

        case 5:
            limparTela();
            a_livros();
            break;
            
        case 6:
            limparTela();
            //e_livros();
            break;

        default:
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

void menuUsuarios()
{

    int resposta;

    while (1)
    {
        exibirTitulo("assets/usuarios.txt");
        printf("\n");
        printf("( 1 ) Listar todos os usuários.\n");
        printf("( 2 ) Pesquisar usuários.\n");
        printf("( 3 ) Cadastrar um usuário.\n");
        printf("( 4 ) Remover algum usuário.\n");
        printf("( 5 ) Alterar algum dado de usuário.\n");
        printf("( 0 ) Retornar.\n");
        printf("\n");

        printf("Selecione a opção que você deseja: ");

        if (scanf("%d", &resposta) != 1)
        {
            erroEntrada("Opção inválida!");
            continue;
        }

        switch (resposta)
        {
        case 0:
            limparTela();
            return;

        case 1:
            limparTela();
            l_usuarios();
            break;

        case 2:
            limparTela();
            p_usuarios();
            break;

        case 3:
            limparTela();
            c_usuarios();
            break;

        case 4:
            limparTela();
            r_usuarios();
            break;

        case 5:
            limparTela();
            a_usuarios();
            break;

        default:
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

void menuEmprestimos(){

    int resposta;

    while (1)
    {
        exibirTitulo("assets/emprestimos.txt");
        printf("\n");
        printf("( 1 ) Pesquisar livros.\n");
        printf("( 2 ) Cadastrar um livro.\n");
        printf("( 3 ) Remover algum livro.\n");
        printf("( 0 ) Retornar.\n");
        printf("\n");

        printf("Selecione a opção que você deseja: ");

        if (scanf("%d", &resposta) != 1)
        {
            erroEntrada("Opção inválida!");
            continue;
        }

        switch (resposta)
        {
        case 0:
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
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

void menuDevolucoes(){

    int resposta;

    while (1)
    {
        exibirTitulo("assets/devolucoes.txt");
        printf("\n");
        printf("( 1 ) Pesquisar livros.\n");
        printf("( 2 ) Cadastrar um livro.\n");
        printf("( 3 ) Remover algum livro.\n");
        printf("( 0 ) Retornar.\n");
        printf("\n");

        printf("Selecione a opção que você deseja: ");

        if (scanf("%d", &resposta) != 1)
        {
            erroEntrada("Opção inválida!");
            continue;
        }

        switch (resposta)
        {
        case 0:
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
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

void menuRelatorios(){

    int resposta;

    while (1)
    {
        exibirTitulo("assets/relatorios.txt");
        printf("\n");
        printf("( 1 ) Pesquisar livros.\n");
        printf("( 2 ) Cadastrar um livro.\n");
        printf("( 3 ) Remover algum livro.\n");
        printf("( 0 ) Retornar.\n");
        printf("\n");

        printf("Selecione a opção que você deseja: ");

        if (scanf("%d", &resposta) != 1)
        {
            erroEntrada("Opção inválida!");
            continue;
        }

        switch (resposta)
        {
        case 0:
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
            erroEntrada("Opção inválida!");
            break;
        }
    }
}
