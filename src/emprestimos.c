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

    FILE *lista_l = fopen("data/ListaLivros.dat", "rb+");
    FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb+");
    FILE *lista_emp = fopen("data/ListaEmprestimos.dat", "ab");

    if (lista_l == NULL || lista_u == NULL || lista_emp == NULL)
    {
        printf("\nErro inesperado ao abrir o arquivo!\n");
        // Garantir o fechamento
        if (lista_l)
            fclose(lista_l);

        if (lista_u)
            fclose(lista_u);

        if (lista_emp)
            fclose(lista_emp);

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
            printf("\nLivro disponível\n\n");
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

    // SALVA NO ARQUIVO BINÁRIO (.dat)
    if (fwrite(&emp, sizeof(struct Emprestimo), 1, lista_emp) != 1)
    {
        printf("Erro ao registrar empréstimo!\n");
    }

    // Fechamento dos arquivos
    fclose(lista_l);
    fclose(lista_u);
    fclose(lista_emp);

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
    int usuarioEncontrado = 0;
    int livroEncontrado = 0;

    // Declarando todos os ponteiros de arquivos no topo da função
    FILE *lista_emp = NULL;
    FILE *lista_u = NULL;
    FILE *lista_l = NULL;

    lista_emp = fopen("data/ListaEmprestimos.dat", "rb");
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
            erroEntrada("Matrícula inválida!");
            fclose(lista_emp);
            return;
        }

        lista_u = fopen("data/ListaUsuarios.dat", "rb");
        if (lista_u == NULL)
        {
            printf("Erro ao abrir arquivo de usuários!\n");
            fclose(lista_emp);
            return;
        }

        while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        {
            if (u.matricula == matricula)
            {
                usuarioEncontrado = 1;
                break;
            }
        }
        fclose(lista_u); // Fecha logo após o uso

        if (!usuarioEncontrado)
        {
            printf("\nUsuário não encontrado!\n");
            fclose(lista_emp);
            pausar();
            return;
        }

        limparBuffer();

        lista_l = fopen("data/ListaLivros.dat", "rb");
        if (lista_l == NULL)
        {
            printf("Erro ao abrir arquivo de livros!\n");
            fclose(lista_emp);
            return;
        }

        while (fread(&emp, sizeof(struct Emprestimo), 1, lista_emp) == 1)
        {
            if (emp.matricula_usuario == matricula && emp.devolvido == 0)
            {
                encontrado = 1;
                rewind(lista_l);

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
            }
        }
        fclose(lista_l); // Fecha após o loop dos empréstimos

        if (!encontrado)
            printf("\nUsuário não possui empréstimos ativos.\n");

        break;

    case 2:
        printf("\nDigite o ID do livro: ");
        if (scanf("%d", &id_livro) != 1)
        {
            erroEntrada("ID inválido!");
            fclose(lista_emp);
            return;
        }

        limparBuffer();

        lista_l = fopen("data/ListaLivros.dat", "rb");
        if (lista_l == NULL) // Adicionada validação que faltava aqui
        {
            printf("Erro ao abrir arquivo de livros!\n");
            fclose(lista_emp);
            return;
        }

        while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
        {
            if (l.id == id_livro)
            {
                livroEncontrado = 1;
                break;
            }
        }
        fclose(lista_l); // Fecha o arquivo de livros pois não precisará mais dele

        if (!livroEncontrado)
        {
            printf("\nLivro não encontrado!\n");
            fclose(lista_emp);
            pausar();
            return;
        }

        // CORREÇÃO: É preciso abrir o arquivo de usuários para poder usá-lo neste case!
        lista_u = fopen("data/ListaUsuarios.dat", "rb");
        if (lista_u == NULL)
        {
            printf("Erro ao abrir arquivo de usuários!\n");
            fclose(lista_emp);
            return;
        }

        while (fread(&emp, sizeof(struct Emprestimo), 1, lista_emp) == 1)
        {
            if (emp.id_livro == id_livro && emp.devolvido == 0)
            {
                encontrado = 1;
                rewind(lista_u);

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
            }
        }

        fclose(lista_u); // Fecha o arquivo de usuários que foi aberto no case 2

        if (!encontrado)
            printf("\nNenhum usuário está com este livro emprestado.\n");

        break;

    default:
        erroEntrada("Opção inválida!");
        break;
    }

    fclose(lista_emp); // Fecha o arquivo principal no fim da função

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

    FILE *lista_emp = fopen("data/ListaEmprestimos.dat", "r");
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

        printf("\n=================================\n");
        printf("EMPRÉSTIMO %d\n", i + 1);
        printf("=================================\n");
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
