#include <stdio.h>
#include <locale.h>
#include<time.h>
#include <stdlib.h>
#include "../include/menu.h"
FILE *lista_l;
struct Livro{
    int id;
    char nome[50];
    char autor[50];
    char genero[50];
    int ano;
    int quant_total;
    int quant_emprestado;
    int quant_disp;
};
void c_livros() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    lista_l = fopen("data/ListaLivros.txt", "ab");
    
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

char livro[50];

void p_livros() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
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
                for(j = 0; l.nome[j] != '\0'; j++)
                    temp[j] = l.nome[j];
                temp[j] = '\0';

                // Converte temp para minúsculo (não modifica o arquivo)
                for(j = 0; temp[j] != '\0'; j++)
                    if(temp[j] >= 'A' && temp[j] <= 'Z')
                        temp[j] = temp[j] + 32;

                // Compara caractere por caractere
                for(i = 0; livro[i] != '\0' && temp[i] != '\0'; i++)
                    if(livro[i] != temp[i])
                        break;

                if(livro[i] == '\0' && temp[i] == '\0'){
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