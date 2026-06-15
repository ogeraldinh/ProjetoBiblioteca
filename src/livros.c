#include "../include/livros.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

void c_livros() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *lista_l = fopen("data/ListaLivros.txt", "ab");
    
    if(lista_l == NULL){
        printf("\nErro inesperado ao abrir o arquivo!\n");
        system("pause");
        exit(1);
    }
    int n, i;
    printf("Quantos livros deseja cadastrar?: ");
    scanf("%d", &n);
    struct Livro *l = malloc(n*sizeof(struct Livro));

    if(l == NULL){
        printf("Erro de alocacao!\n");
        fclose(lista_l);
        exit(1);
    }
    
    //Randomizador de ID (7 Algorismos)
    srand(time(NULL));
    for(i = 0; i < n; i++){
        l[i].id = 1000000 + rand() % 9000000;
        //Entrada dos dados pelo usuário.
        printf("Digite o Nome do livro que queira cadastrar: ");
        scanf(" %[^\n]", l[i].nome);
        printf("Digite o Nome do Autor(a): ");
        scanf(" %[^\n]", l[i].autor);
        printf("Digite o gênero do livro: ");
        scanf(" %[^\n]", l[i].genero);
        printf("Digite o ano de publicação(usando números): ");
        scanf("%d", &l[i].ano);
        printf("Digite a quantidade total do livro: ");
        scanf("%d", &l[i].quant_total);
        printf("Digite a quantidade de livros emprestados: ");
        scanf("%d", &l[i].quant_emprestado);
        printf("O ID do seu livro sera: %d\n", l[i].id);
        // concertar essa variável
        l[i].quant_disp = l[i].quant_total - l[i].quant_emprestado;
        printf("A quantidade disponível é %d\n", l[i].quant_disp);
    }

    fwrite(l, sizeof(struct Livro), n, lista_l);
    free(l);
    fclose(lista_l);
    system("pause");
}

void p_livros() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    char livro[50];
    
    struct Livro l;
    int pesq, i, j;
    int id_livro;
    int encontrado = 0;
    
    FILE *lista_l = fopen("data/ListaLivros.txt", "rb");
    if(lista_l == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    printf("A pesquisa vai ser por id ou nome?\n");
    printf("(1) Nome\n");
    printf("(2) ID\n");
    scanf("%d", &pesq);
    switch(pesq){
        case 1:

            printf("Digite o livro que deseja procurar: ");
            scanf(" %[^\n]", livro);

            // Converte o livro buscado para minúsculo
            for(i = 0; livro[i] != '\0'; i++){
                if(livro[i] >= 'A' && livro[i] <= 'Z')
                    livro[i] = livro[i] + 32;
            }
            while(fread(&l, sizeof(struct Livro), 1, lista_l) == 1){
                // temp para copiar o livro no arquivo e passar para minusculo
                char temp[50];
                strcpy(temp, l.nome);

                // Converte temp para minúsculo (não modifica o arquivo)
                for(j = 0; temp[j] != '\0'; j++)
                    if(temp[j] >= 'A' && temp[j] <= 'Z')
                        temp[j] = temp[j] + 32;


                if(strcmp(livro, temp) == 0){
                    encontrado = 1;
                    printf("O livro esta no sistema!\n");
                    printf("ID: %d\n", l.id);
                    printf("Nome: %s\n", l.nome);
                    printf("Autor: %s\n", l.autor);
                    printf("Genero: %s\n", l.genero);
                    printf("Ano: %d\n", l.ano);
                    printf("Qtd. total: %d\n", l.quant_total);
                    printf("Qtd. emprestado: %d\n", l.quant_emprestado);
                    printf("Disponiveis: %d\n", l.quant_disp);
                }
            }

            if(!encontrado)
                printf("Livro nao esta cadastrado no sistema.\n");

            break;

        case 2:
            //Entrada de dados do ID
            printf("Digite o ID do livro que deseja buscar(7 algarismos): ");
            scanf("%d", &id_livro);

            // Enquanto fread não achar ou chegar ao EOF
            while(fread(&l, sizeof(struct Livro), 1, lista_l) == 1){
                if(l.id == id_livro){
                    encontrado = 1;
                    printf("O livro esta no sistema!\n");
                    printf("ID: %d\n", l.id);
                    printf("Nome: %s\n", l.nome);
                    printf("Autor: %s\n", l.autor);
                    printf("Genero: %s\n", l.genero);
                    printf("Ano: %d\n", l.ano);
                    printf("Qtd. total: %d\n", l.quant_total);
                    printf("Qtd. emprestado: %d\n", l.quant_emprestado);
                    printf("Disponiveis: %d\n", l.quant_disp);
                    break;
                }

            }
            if(!encontrado)
                printf("Livro nao esta cadastrado no sistema.\n");
            break;
        default:
            printf("Opcao invalidade... tente novamente\n");
            return;

    }
    fclose(lista_l);
    system("pause");
}

void r_livros() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int id_r;
    int encontrado = 0;
    struct Livro l;

    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d", &id_r);

    //abrir original para ReadB
    FILE *lista_ori = fopen("data/ListaLivros.txt", "rb");
    if(lista_ori == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    //abrir um temporario para WriteB
    FILE *lista_t = fopen("data/temp.txt", "wb");
    if(lista_t == NULL){
        printf("Erro ao criar arquivo temporario!\n");
        fclose(lista_ori);
        exit(1);
    }

    //acha o livro que vai ser removido e não copia no temp
    while(fread(&l, sizeof(struct Livro), 1, lista_ori) == 1){
        if(l.id != id_r){
            fwrite(&l, sizeof(struct Livro), 1, lista_t);
        } else {
            encontrado = 1;
            printf("Livro '%s' removido com sucesso!\n", l.nome);
        }
    }

    fclose(lista_ori);
    fclose(lista_t);

    if(!encontrado){
        printf("Livro nao encontrado!\n");
        //se ID não achado cancela a temp e não altera a original
        remove("data/temp.txt");
        exit(1);
    }

    //remove o original e dá rename na temp para nova original
    remove("data/ListaLivros.txt");
    rename("data/temp.txt", "data/ListaLivros.txt");
    system("pause");
}