// Bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>

// Módulos Locais
#include "../include/menu.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/emprestimos.h"
#include "../include/relatorios.h"
#include "../include/auxiliares.h"


// Função de execução do menu principal
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
        printf("( 3 ) Gerenciar empréstimos.\n");
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

// Função de execução do submenu de livros
void menuLivros()
{
    int resposta;

    while (1)
    {
        exibirTitulo("assets/livros.txt");
        printf("\n");
        printf("( 1 ) Listar todos os livros.\n");
        printf("( 2 ) Pesquisar livros.\n");
        printf("( 3 ) Cadastrar livro.\n");
        printf("( 4 ) Remover livro.\n");
        printf("( 5 ) Atualizar dados de livro.\n");
        /* Informar, para um dado livro, para quais usuários ele está emprestado no momento
        (caso não haja, informar que o livro não possui empréstimos);*/
        printf("( 6 ) Empréstimos de livros.\n");
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
            e_livros();
            break;

        default:
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

// Função de execução do submenu de usuários
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

// Função de execução do submenu de empréstimos
void menuEmprestimos()
{

    int resposta;

    while (1)
    {
        exibirTitulo("assets/emprestimos.txt");
        printf("\n");
        printf("( 1 ) Listar empréstimos.\n");
        printf("( 2 ) Buscar empréstimos.\n");
        printf("( 3 ) Registrar empréstimo.\n");
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
            l_emprestimos();
            break;

        case 2:
            limparTela();
            p_emprestimos();
            break;

        case 3:
            limparTela();
            c_emprestimos();
            break;

        case 4:
            limparTela();
            d_emprestimos();
            break;

        default:
            erroEntrada("Opção inválida!");
            break;
        }
    }
}

// Função de execução do submenu de registro de devolução
void menuDevolucoes()
{

    while (1)
    {
        exibirTitulo("assets/devolucao.txt");
        printf("\n");
        d_emprestimos();
        return;
    }
}

// Função de execução do submenu de relatórios
void menuRelatorios()
{

    int resposta;

    while (1)
    {
        exibirTitulo("assets/relatorios.txt");
        printf("\n");
        printf("( 1 ) Criar relatorio de livros mais emprestados.\n");
        printf("( 2 ) Gerar relatório de usuários em atraso.\n");
        printf("( 3 ) Gerar relatório com todo acervo disponível.\n");
        printf("( 4 ) Gerar relatório de histórico de empréstimos de um Usuário.\n");
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
            lm_relatorio();
            break;

        case 2:
            limparTela();
            a_relatorio();
            break;

        case 3:
            limparTela();
            ad_relatorio();
            break;
        case 4:
            limparTela();
            h_relatorio();
            break;

        default:
            erroEntrada("Opção inválida!");
            break;
        }
    }
}
