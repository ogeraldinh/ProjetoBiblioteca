#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>

void c_emprestimos()
{
    int matricula_usuario;
    int id_livro;
    int encontrado = 0;
    long posUsuario;
    long posLivro;

    struct Usuario u;
    struct Emprestimo emp;
    struct Livro l;

    FILE *lista_emp = fopen("data/ListaEmprestimos.txt", "a");
    FILE *lista_l = fopen("data/ListaLivros.dat", "rb+");
    FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb+");

    if (lista_emp == NULL || lista_l == NULL || lista_u == NULL)
    {
        printf("\nErro inesperado ao abrir o arquivo!\n");
        // Garantir o fechamento
        if (lista_emp)
            fclose(lista_emp);
        if (lista_l)
            fclose(lista_l);
        if (lista_u)
            fclose(lista_u);
        pausar();
        return;
    }

    exibirTitulo("assets/emprestimos.txt");
    printf("\n");

    // Entrada de dados da matrícula
    printf("\nDigite a matrícula do usuário que deseja buscar (5 algarismos): ");
    if (scanf("%d", &matricula_usuario) != 1)
    {
        printf("\nMatrícula inválida! Digite apenas números.\n");
        limparBuffer();
        fclose(lista_emp);
        fclose(lista_l);
        fclose(lista_u);
        pausar();
        return;
    }
    limparBuffer();

    // Busca pelo Usuário
    encontrado = 0;
    while (1)
    {
        // Guarda a posição ANTES de ler o registro
        posUsuario = ftell(lista_u);

        if (fread(&u, sizeof(struct Usuario), 1, lista_u) != 1)
        {
            break; // EOF ou Erro
        }

        if (u.matricula == matricula_usuario)
        {
            encontrado = 1;
            emp.matricula_usuario = matricula_usuario;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Usuário não encontrado!\n");
        fclose(lista_emp);
        fclose(lista_l);
        fclose(lista_u);
        pausar();
        return;
    }

    if (u.quant_emprestimos_ativos >= 3)
    {
        printf("Usuário atingiu o limite de empréstimos! (Máx. 3)\n");
        fclose(lista_emp);
        fclose(lista_l);
        fclose(lista_u);
        pausar();
        return;
    }

    // Entrada de dados do Livro
    printf("\nDigite o ID do livro a ser emprestado (5 algarismos): ");
    if (scanf("%d", &id_livro) != 1)
    {
        printf("\nID inválido! Digite apenas números.\n");
        limparBuffer();
        fclose(lista_emp);
        fclose(lista_l);
        fclose(lista_u);
        pausar();
        return;
    }
    limparBuffer();

    // Busca pelo Livro
    encontrado = 0;
    while (1)
    {
        // Guarda a posição ANTES de ler o livro
        posLivro = ftell(lista_l);

        if (fread(&l, sizeof(struct Livro), 1, lista_l) != 1)
        {
            break; // EOF ou Erro
        }

        if (l.id == id_livro)
        {
            encontrado = 1;
            printf("\nLivro encontrado!\n");
            printf("Título: %s\n", l.nome);
            printf("Autor: %s\n", l.autor);
            printf("Disponíveis: %d\n", l.quant_disp);
            emp.id_livro = id_livro;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Livro não encontrado!\n");
        fclose(lista_emp);
        fclose(lista_l);
        fclose(lista_u);
        pausar();
        return;
    }

    if (l.quant_disp < 1)
    {
        printf("Não foi possível realizar o empréstimo! (Livro indisponível)\n");
        fclose(lista_emp);
        fclose(lista_l);
        fclose(lista_u);
        pausar();
        return;
    }

    // Geração de dados do empréstimo
    emp.id_emprestimo = 10000000 + rand() % 90000000;
    obterDataAtual(emp.data_retirada);
    obterDataFutura(emp.data_prevista, 14);
    emp.devolvido = 0;
    emp.data_devolucao[0] = '\0';

    // Atualização do Usuário (vai direto para a posição guardada)
    u.quant_emprestimos_ativos++;
    fseek(lista_u, posUsuario, SEEK_SET);
    if (fwrite(&u, sizeof(struct Usuario), 1, lista_u) != 1)
    {
        printf("Erro ao atualizar usuário!\n");
    }

    // Atualização do Livro (vai direto para a posição guardada)
    l.quant_disp--;
    l.quant_emprestado++;
    l.total_emprestimos++;
    fseek(lista_l, posLivro, SEEK_SET);
    if (fwrite(&l, sizeof(struct Livro), 1, lista_l) != 1)
    {
        printf("Erro ao atualizar livro!\n");
    }

    // Gravação do Empréstimo em formato legível
    if (fprintf(lista_emp,
                "\n========================================\n"
                "ID Empréstimo: %d\n"
                "ID Livro: %d\n"
                "Matrícula do Usuário: %d\n"
                "Data de Retirada: %s\n"
                "Data Prevista: %s\n"
                "Data de Devolução: %s\n"
                "Devolvido: %s\n"
                "========================================\n",
                emp.id_emprestimo,
                emp.id_livro,
                emp.matricula_usuario,
                emp.data_retirada,
                emp.data_prevista,
                emp.data_devolucao[0] == '\0' ? "Não devolvido" : emp.data_devolucao,
                emp.devolvido ? "Sim" : "Não") < 0)
    {
        printf("Erro ao registrar empréstimo!\n");
    }

    // Fechamento dos arquivos
    fclose(lista_emp);
    fclose(lista_l);
    fclose(lista_u);

    printf("\nEmpréstimo realizado com sucesso!\n");
    printf("ID do empréstimo: %d\n", emp.id_emprestimo);
    printf("Data de retirada: %s\n", emp.data_retirada);
    printf("Data prevista: %s\n", emp.data_prevista);
    pausar();
}

void p_emprestimos()
{
    struct Emprestimo emp;
    struct Livro l;
    struct Usuario u;

    int opcao;
    int matricula;
    int id_livro;
    int encontrado = 0;

    FILE *lista_emp = fopen("data/ListaEmprestimos.txt", "rb");

    if (lista_emp == NULL)
    {
        printf("Erro ao abrir arquivo de empréstimos!\n");
        pausar();
        return;
    }

    exibirTitulo("assets/emprestimos.txt");

    printf("\n");
    printf("(1) Buscar empréstimos de um usuário\n");
    printf("(2) Buscar usuários de um livro\n");
    printf("\n");

    printf("Selecione uma opção: ");

    if (scanf("%d", &opcao) != 1)
    {
        limparBuffer();
        fclose(lista_emp);
        erroEntrada("Entrada inválida!");
        return;
    }

    limparBuffer();

    switch (opcao)
    {
    case 1:

        printf("\nDigite a matrícula do usuário: ");

        if (scanf("%d", &matricula) != 1)
        {
            limparBuffer();
            erroEntrada("Matrícula inválida!");
            fclose(lista_emp);
            return;
        }

        limparBuffer();

        while (fread(&emp, sizeof(struct Emprestimo), 1, lista_emp) == 1)
        {
            if (emp.matricula_usuario == matricula &&
                emp.devolvido == 0)
            {
                encontrado = 1;

                FILE *lista_l = fopen("data/ListaLivros.dat", "rb");

                if (lista_l != NULL)
                {
                    while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
                    {
                        if (l.id == emp.id_livro)
                        {
                            printf("\n---------------------------\n");
                            printf("ID Empréstimo: %d\n", emp.id_emprestimo);
                            printf("Livro: %s\n", l.nome);
                            printf("Autor: %s\n", l.autor);
                            printf("Data retirada: %s\n", emp.data_retirada);
                            printf("Data prevista: %s\n", emp.data_prevista);
                            printf("---------------------------\n");
                            break;
                        }
                    }

                    fclose(lista_l);
                }
            }
        }

        if (!encontrado)
            printf("\nUsuário não possui empréstimos ativos.\n");

        break;

    case 2:

        printf("\nDigite o ID do livro: ");

        if (scanf("%d", &id_livro) != 1)
        {
            limparBuffer();
            erroEntrada("ID inválido!");
            fclose(lista_emp);
            return;
        }

        limparBuffer();

        while (fread(&emp, sizeof(struct Emprestimo), 1, lista_emp) == 1)
        {
            if (emp.id_livro == id_livro &&
                emp.devolvido == 0)
            {
                encontrado = 1;

                FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb");

                if (lista_u != NULL)
                {
                    while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
                    {
                        if (u.matricula == emp.matricula_usuario)
                        {
                            printf("\n---------------------------\n");
                            printf("Matrícula: %d\n", u.matricula);
                            printf("Nome: %s\n", u.nome);
                            printf("Curso: %s\n", u.curso);
                            printf("Data retirada: %s\n", emp.data_retirada);
                            printf("Data prevista: %s\n", emp.data_prevista);
                            printf("---------------------------\n");
                            break;
                        }
                    }

                    fclose(lista_u);
                }
            }
        }

        if (!encontrado)
            printf("\nNenhum usuário está com este livro emprestado.\n");

        break;

    default:
        erroEntrada("Opção inválida!");
        break;
    }

    fclose(lista_emp);

    pausar();
    limparTela();
}

void l_emprestimos()
{
    struct Usuario u;
    struct Emprestimo emp;
    struct Livro l;

    int i = 0;
    int totalPendentes = 0;
    int totalDevolvidos = 0;

    FILE *lista_emp = fopen("data/ListaEmprestimos.txt", "r");
    FILE *lista_l = fopen("data/ListaLivros.dat", "rb");
    FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb");

    if (lista_emp == NULL || lista_l == NULL || lista_u == NULL)
    {
        printf("Erro ao abrir arquivo!\n");

        if (lista_emp)
            fclose(lista_emp);
        if (lista_l)
            fclose(lista_l);
        if (lista_u)
            fclose(lista_u);

        pausar();
        return;
    }

    while (fread(&emp, sizeof(struct Emprestimo), 1, lista_emp) == 1)
    {
        rewind(lista_u);

        while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        {
            if (u.matricula == emp.matricula_usuario)
                break;
        }

        rewind(lista_l);

        while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
        {
            if (l.id == emp.id_livro)
                break;
        }

        printf("\n========================================\n");
        printf("EMPRÉSTIMO %d\n", i + 1);
        printf("========================================\n");
        printf("ID Empréstimo : %d\n", emp.id_emprestimo);
        printf("Usuário       : %s (%d)\n", u.nome, u.matricula);
        printf("Livro         : %s\n", l.nome);
        printf("Retirada      : %s\n", emp.data_retirada);
        printf("Prevista      : %s\n", emp.data_prevista);

        if (emp.devolvido)
        {
            printf("Devolução     : %s\n", emp.data_devolucao);
            printf("Status        : DEVOLVIDO\n");
        }
        else
        {
            printf("Status        : PENDENTE\n");
        }
        i++;
    }

    if (i == 0)
    {
        printf("\nNenhum empréstimo registrado.\n");
    }

    printf("\n=================================\n");
    printf("Total de empréstimos: %d\n", totalPendentes + totalDevolvidos);
    printf("Pendentes: %d\n", totalPendentes);
    printf("Devolvidos: %d\n", totalDevolvidos);
    printf("=================================\n");

    fclose(lista_emp);
    fclose(lista_l);
    fclose(lista_u);
    pausar();
    limparBuffer();
    limparTela();
}

void a_emprestimos() {}
