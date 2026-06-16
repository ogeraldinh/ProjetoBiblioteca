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
    int n, i, j;
    struct Livro temp;
    FILE *lista_l = fopen ("data/ListaLivros.txt", "rb");
    if(lista_l == NULL){
        printf("Erro na abertura do arquivo!\n");
        pausar();
        limparTela();
        return;
    }

    //quantos livros registrados
    fseek(lista_l, 0, SEEK_END);
    n = ftell(lista_l)/sizeof(struct Livro);
    rewind(lista_l);
    //fazer malloc para bubble sort
    struct Livro *l = malloc(n*sizeof(struct Livro));
    
    if(l == NULL){
        printf("Erro na alocaçao dinamica!\n");
        fclose(lista_l);
        system("pause");
        return;
    }

    //lê todos os registros e fecha
    fread(l, sizeof(struct Livro), n, lista_l);
    fclose(lista_l);

    for(i=0; i < n; i++){
        for(j = 0; j< (n-1); j++){
            if(l[j].v_emp < l[j+1].v_emp){
                temp = l[j];
                l[j] = l[j+1];
                l[j+1] = temp;
            }
        }
    }

    FILE *lm_r = fopen("data/RelatorioMaisEmprestado.txt", "w");
    if(lm_r == NULL){
        printf("Erro na abertura do arquivo!\n");
        system("pause");
        return;
    }
    fprintf(lm_r, "<-----TOP livros mais emprestados----->\n");
    for(i=0; i < n; i++){
        fprintf(lm_r, "Livro %d: %s || Vezes emprestado: %d\n", i+1, l[i].nome, l[i].v_emp);
    }
    fclose(lm_r);
    free(l);
    printf("Relatorio criado em data/RelatorioMaisEmprestado.txt: por favor consultar o arquivo!!!\n");
    limparBuffer();
    pausar();
    limparTela();
}

void a_relatorio()
{
    int dia, mes, ano;
    printf("Insira a data hoje: ");
    printf("Dia: ");
    scanf("%d", &dia);
    printf("Mês: ");
    scanf("%d", &mes);
    printf("Ano: ");
    scanf("%d", &ano);

    struct Emprestimo e;
    struct Usuario u;
    struct Livro l;
    // diz quantos dias no total tem hoje 
    int hoje = (dia + (mes-1)*30 + ano*365);
    FILE *lista_e = fopen("data/ListaEmprestimos.txt", "rb");

    if(lista_e == NULL){
        printf("Erro na abertura do arquivo!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }
    FILE *a_r = fopen("RelatorioAtrasos.txt", "w");

    if(a_r == NULL){
        printf("Erro na abertura do arquivo!\n");
        fclose(lista_e);
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    fprintf(a_r, "↓↓↓↓ EMPRESTIMOS EM ATRASO ↓↓↓↓\n");

    while(fread(&e, sizeof(struct Emprestimo), 1, lista_e) == 1){
        if(e.devolvido == 1)
            continue;
        int dia_dev = (e.data_dev[2]*365 + ((e.data_dev[1]-1)*30) + e.data_dev[0]);
        int diferenca = hoje - dia_dev;
        if(diferenca > 0){
            FILE *lista_u = fopen("data/ListaUsuarios.txt", "rb");
            while(fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
                if(u.matricula == e.matricula_usuario) break;
            fclose(lista_u);

            FILE *lista_l = fopen("data/ListaLivros.txt", "rb");
            while(fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
                if(l.id == e.id_livro) break;
            fclose(lista_l);

            fprintf(a_r, "Usuario:   %s (matricula: %d)\n", u.nome, u.matricula);
            fprintf(a_r, "Livro:     %s\n", l.nome);
            fprintf(a_r, "Devolucao: %d/%d/%d\n", e.data_dev[0], e.data_dev[1], e.data_dev[2]);
            fprintf(a_r, "Atraso:    %d dia(s)\n\n", diferenca);
        }
    }
    fclose(lista_e);
    fclose(a_r);
    printf("Relatorio criado em data/RelatorioAtrasos.txt: por favor conferir!\n");
    limparBuffer();
    pausar();
    limparTela();

}

void ad_relatorio() 
{
    struct Livro l;
    int i = 0;

    FILE *lista_l = fopen("data/ListaLivros.txt", "rb");
    if(lista_l == NULL){
        printf("Erro ao abrir arquivo!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    FILE *ad_r = fopen("data/RelatorioAcervoDisponivel.txt", "w");
    if(ad_r == NULL){
        printf("Erro ao abrir o arquivo!\n");
        fclose(lista_l);
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    fprintf(ad_r, "↓↓↓↓ ACERVO DISPONIVEL ↓↓↓↓\n");

    while(fread(&l, sizeof(struct Livro), 1, lista_l) == 1){
        if(l.quant_disp > 0){
            fprintf(ad_r, "Livro %d: %s || ID: %d || Autor: %s || Genero: %s || Ano: %d\n", i+1, l.nome, l.id, l.autor, l.genero, l.ano);
            fprintf(ad_r, "---> Qtd. Disponivel: %d de %d <---\n", l.quant_disp, l.quant_total);
            i++;
        }
    }

    if(i == 0)
        fprintf(ad_r, "Nenhum livro disponivel no momento.\n");
    else
        fprintf(ad_r, "Total de livros disponiveis: %d\n", i);

    fclose(lista_l);
    fclose(ad_r);
    printf("Relatorio salvo em data/RelatorioAcervoDisponivel.txt: por favor conferir\n");
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

    FILE *lista_u = fopen("data/ListaUsuarios.txt", "rb");
    if(lista_u == NULL){
        printf("Erro ao abrir o arquivo!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }
    while(fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        if(u.matricula == pesq){
            usuario_encontrado = 1;
            break;
        }
    fclose(lista_u);

    if(usuario_encontrado == 0){
        printf("Usuario nao encontrado!\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    FILE *lista_e = fopen("data/ListaEmprestimos.txt", "rb");
    if(lista_e == NULL){
        printf("Nenhum emprestimo registrado.\n");
        limparBuffer();
        pausar();
        limparTela();
        return;
    }


    FILE *h_r = fopen("HistoricoRelatorio", "w");
    if(h_r == NULL){
        printf("Erro ao abrir arquivo!\n");
        fclose(lista_e);
        limparBuffer();
        pausar();
        limparTela();
        return;
    }

    fprintf(h_r, "↓↓↓↓ HISTORICO DE EMPRESTIMOS ↓↓↓↓\n");
    fprintf(h_r, "Usuario: %s //// Matricula: %d\n", u.nome, u.matricula);

    while(fread(&e, sizeof(struct Emprestimo), 1, lista_e) == 1){
        if(e.matricula_usuario == pesq){
            i++;

            FILE *arq_l = fopen("data/ListaLivros.txt", "rb");
            while(fread(&l, sizeof(struct Livro), 1, arq_l) == 1)
                if(l.id == e.id_livro) break;
            fclose(arq_l);

            fprintf(h_r, "Livro %d: %s\n", i, l.nome);
            fprintf(h_r, "ID emprestimo: %d\n", e.id_emprestimo);
            fprintf(h_r, "Emprestado em: %d / %d / %d\n", e.data_emp[0], e.data_emp[1], e.data_emp[2]);
            fprintf(h_r, "Devolucao em:  %d / %d / %d\n", e.data_dev[0], e.data_dev[1], e.data_dev[2]);
            if(e.devolvido == 1){
                fprintf(h_r, "   Status: %d || Devolvido : OK", e.devolvido);
            } else{
                fprintf(h_r, "   Status: %d || Devolvido : Pendente", e.devolvido);
                }
        }
    }

    if(i == 0)
        fprintf(h_r, "Nenhum emprestimo encontrado.\n");
    else
        fprintf(h_r, "Total de emprestimos: %d\n", i);

    fclose(lista_e);
    fclose(h_r);
    printf("Relatorio salvo em data/HistoricoRelatorio.txt: por favor conferir!\n");
    printf("AVISO: Se for gerado mais histórico, o anterior vai ser sobrescrito!! Por Favor guardar\n");
    limparBuffer();
    pausar();
    limparTela();
}