#include "../include/relatorios.h"
#include "../include/auxiliares.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/emprestimos.h"

#include <stdio.h>
#include <stdlib.h>

/*Livros mais emprestados (ordenados de forma decrescente pelo número total de
empréstimos); */

void lm_relatorio()
{
    size_t n, i, j;
    struct Livro temp;
    FILE *lista_l = fopen("data/ListaLivros.dat", "rb");
    if (lista_l == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        pausar();
        limparTela();
        return;
    }

    // quantos livros registrados
    fseek(lista_l, 0, SEEK_END);
    n = (size_t)ftell(lista_l) / sizeof(struct Livro);
    if (n == 0)
    {
        printf("Nenhum livro cadastrado.\n");
        fclose(lista_l);
        pausar();
        return;
    }
    rewind(lista_l);
    // fazer malloc para bubble sort
    struct Livro *l = malloc(n * sizeof(struct Livro));

    if (l == NULL)
    {
        printf("Erro na alocaçao dinamica!\n");
        fclose(lista_l);
        system("pause");
        return;
    }

    // lê todos os registros e fecha
    if (fread(l, sizeof(struct Livro), n, lista_l) != n)
    {
        printf("Erro ao ler os registros.\n");
        free(l);
        fclose(lista_l);
        return;
    }
    fclose(lista_l);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (l[j].total_emprestimos < l[j + 1].total_emprestimos)
            {
                temp = l[j];
                l[j] = l[j + 1];
                l[j + 1] = temp;
            }
        }
    }

    FILE *lm_r = fopen("relatorios/RelatoriosGenericos/RelatorioMaisEmprestado.txt", "w");
    if (lm_r == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        system("pause");
        free(l);
        return;
    }
    fprintf(lm_r, "<-----TOP livros mais emprestados----->\n");
    printf("<-----TOP livros mais emprestados----->\n");
    for (i = 0; i < n; i++)
    {
        fprintf(lm_r, "Livro %d: %s || Total de emprestimos: %d\n", i + 1, l[i].nome, l[i].total_emprestimos);
        printf("Livro %d: %s || Total de emprestimos: %d\n", i + 1, l[i].nome, l[i].total_emprestimos);
    }
    fclose(lm_r);
    free(l);
    printf("\nRelatorio criado em relatorios/RelatoriosGenericos/RelatorioMaisEmprestado.txt: por favor consultar o arquivo!!!\n");
    limparBuffer();
    pausar();
    limparTela();
}

void a_relatorio()
{
    char hojeStr[11];

    obterDataAtual(hojeStr);

    int hoje =
        converterDataParaDias(hojeStr);

    struct Emprestimo e;
    struct Usuario u;
    struct Livro l;

    FILE *lista_e = fopen("data/ListaEmprestimos.dat", "rb");

    if (lista_e == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }
    FILE *a_r = fopen("relatorios/RelatoriosGenericos/RelatorioAtrasos.txt", "w");

    if (a_r == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        fclose(lista_e);
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    fprintf(a_r, "↓↓↓↓ EMPRESTIMOS EM ATRASO ↓↓↓↓\n");
    printf("↓↓↓↓ EMPRESTIMOS EM ATRASO ↓↓↓↓\n");

    while (fread(&e, sizeof(struct Emprestimo), 1, lista_e) == 1)
    {
        if (e.devolvido == 1)
            continue;
        int dataPrevista = converterDataParaDias(e.data_prevista);
        int diferenca = hoje - dataPrevista;
        if (diferenca > 0)
        {
            FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb");
            if (lista_u == NULL)
                continue;
            while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
                if (u.matricula == e.matricula_usuario)
                    break;
            fclose(lista_u);

            FILE *lista_l = fopen("data/ListaLivros.dat", "rb");
            if (lista_l == NULL)
                continue;
            while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
                if (l.id == e.id_livro)
                    break;
            fclose(lista_l);

            fprintf(a_r, "Usuario:   %s (matricula: %d)\n", u.nome, u.matricula);
            fprintf(a_r, "Livro:     %s\n", l.nome);
            fprintf(a_r, "Devolucao prevista: %s\n", e.data_prevista);
            fprintf(a_r, "Atraso:    %d dia(s)\n\n", diferenca);
            printf("Usuario:   %s (matricula: %d)\n", u.nome, u.matricula);
            printf("Livro:     %s\n", l.nome);
            printf("Devolucao prevista: %s\n", e.data_prevista);
            printf("Atraso:    %d dia(s)\n\n", diferenca);
        }
    }
    fclose(lista_e);
    fclose(a_r);
    printf("\nRelatorio criado em relatorios/RelatoriosGenericos/RelatorioAtrasos.txt: por favor conferir!\n");
    limparBuffer();
    pausar();
    limparTela();
}

void ad_relatorio()
{
    struct Livro l;
    int i = 0;

    FILE *lista_l = fopen("data/ListaLivros.dat", "rb");
    if (lista_l == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    FILE *ad_r = fopen("relatorios/RelatoriosGenericos/RelatorioAcervoDisponivel.txt", "w");
    if (ad_r == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        fclose(lista_l);
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    fprintf(ad_r, "↓↓↓↓ ACERVO DISPONIVEL ↓↓↓↓\n");
    printf("↓↓↓↓ ACERVO DISPONIVEL ↓↓↓↓\n");

    while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
    {
        if (l.quant_disp > 0)
        {
            fprintf(ad_r, "Livro %d: %s || ID: %d || Autor: %s || Genero: %s || Ano: %d\n", i + 1, l.nome, l.id, l.autor, l.genero, l.ano);
            fprintf(ad_r, "---> Qtd. Disponivel: %d de %d <---\n\n\n", l.quant_disp, l.quant_total);
            printf("Livro %d: %s || ID: %d || Autor: %s || Genero: %s || Ano: %d\n", i + 1, l.nome, l.id, l.autor, l.genero, l.ano);
            printf("---> Qtd. Disponivel: %d de %d <---\n\n\n", l.quant_disp, l.quant_total);
            i++;
        }
    }

    if (i == 0){
        fprintf(ad_r, "Nenhum livro disponivel no momento.\n");
        printf("Nenhum livro disponivel no momento.\n");
    }
    else{
        fprintf(ad_r, "Total de livros disponiveis: %d\n", i);
        printf("Total de livros disponiveis: %d\n", i);
    }
    fclose(lista_l);
    fclose(ad_r);
    printf("\nRelatorio salvo em relatorios/RelatoriosGenericos/RelatorioAcervoDisponivel.txt: por favor conferir\n");
    limparBuffer();
    pausar();
    limparTela();
}

void h_relatorio()
{
    int pesq;
    struct Emprestimo e;
    struct Livro l;
    struct Usuario u;
    int usuario_encontrado = 0, i = 0;

    printf("Digite a matricula do usuario: ");
    scanf("%d", &pesq);
    limparBuffer();

    FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb");
    if (lista_u == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }
    while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        if (u.matricula == pesq)
        {
            usuario_encontrado = 1;
            break;
        }
    fclose(lista_u);

    if (usuario_encontrado == 0)
    {
        printf("Usuario nao encontrado!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    FILE *lista_e = fopen("data/ListaEmprestimos.dat", "rb");
    if (lista_e == NULL)
    {
        printf("Nenhum emprestimo registrado.\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    char arq[50];
    sprintf(arq, "relatorios/RelatoriosEspecificos/Hist_%d.txt", pesq);
    FILE *h_r = fopen(arq, "w");

    if (h_r == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        fclose(lista_e);
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    fprintf(h_r, "↓↓↓↓ HISTORICO DE EMPRESTIMOS ↓↓↓↓\n\n");
    fprintf(h_r, "Usuario: %s //// Matricula: %d\n", u.nome, u.matricula);
    printf("↓↓↓↓ HISTORICO DE EMPRESTIMOS ↓↓↓↓\n\n");
    printf("Usuario: %s //// Matricula: %d\n", u.nome, u.matricula);

    while (fread(&e, sizeof(struct Emprestimo), 1, lista_e) == 1)
    {
        if (e.matricula_usuario == pesq)
        {
            i++;

            FILE *arq_l = fopen("data/ListaLivros.dat", "rb");
            if (arq_l == NULL)
                continue;
            while (fread(&l, sizeof(struct Livro), 1, arq_l) == 1)
                if (l.id == e.id_livro)
                    break;
            fclose(arq_l);
            
            fprintf(h_r, "Livro %d: %s\n", i, l.nome);
            fprintf(h_r, "ID emprestimo: %d\n", e.id_emprestimo);
            fprintf(h_r, "Emprestado em: %s\n", e.data_retirada);
            fprintf(h_r, "Devolucao prevista: %s\n\n", e.data_prevista);

            printf("Livro %d: %s\n", i, l.nome);
            printf("ID emprestimo: %d\n", e.id_emprestimo);
            printf("Emprestado em: %s\n", e.data_retirada);
            printf("Devolucao prevista: %s\n\n", e.data_prevista);

            if (e.devolvido)
            {
                fprintf(h_r, "Status: Devolvido\n");
                fprintf(h_r, "Data devolucao: %s\n\n", e.data_devolucao);
            
                printf("Status: Devolvido\n");
                printf("Data devolucao: %s\n\n", e.data_devolucao);
            }
            else
            {
                fprintf(h_r, "Status: Pendente\n\n");
                printf("Status: Pendente\n\n");
            }
        }
    }

    if (i == 0){
        fprintf(h_r, "Nenhum emprestimo encontrado.\n");
        
        printf("Nenhum emprestimo encontrado.\n");
    }
    else{
        fprintf(h_r, "Total de emprestimos: %d\n", i);
        printf("Total de emprestimos: %d\n", i);
    }
    fclose(lista_e);
    fclose(h_r);
    printf("\nRelatorio salvo em relatorios/RelatoriosEspecificos: por favor conferir!\n");
    printf("\nAVISO: Se for gerado mais histórico do mesmo usuário, o anterior vai ser sobrescrito!! Por Favor guardar\n");
    limparBuffer();
    pausar();
    limparTela();
}
