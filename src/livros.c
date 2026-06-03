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
    lista_l = fopen("../data/ListaLivros.txt", "ab");

    if(lista_l == NULL){
        printf("\nErro inesperado!\n");
        system("pause");
        exit(1);
    }

    struct Livro l;
    //Randomizador de ID (7 Algorismos)
    srand(clock());
    l.id = 1000000 + rand() % 9000000;
    //Entrada dos dados pela usuário.
    printf("Digite o Nome do livro que queira cadastrar: ");
    scanf(" %[^\n]", l.nome);
    printf("Digite o Nome do Autor(a): ");
    scanf(" %[^\n]", l.autor);
    printf("Digite o gênero do livro: ");
    scanf(" %[^\n]", l.genero);
    printf("Digite o ano de publicação(usando números): ");
    scanf("%d", &l.ano);
    printf("Digite a quantidade total do livro: ");
    scanf("%d", &l.quant_total);
    printf("Digite a quantidade de livros emprestados: ");
    scanf("%d", &l.quant_emprestado);
    // concertar essa variável
    l.quant_disp = l.quant_total - l.quant_emprestado;
    printf("A quantidade disponível é %d", l.quant_disp);

    fwrite(&l, sizeof(struct Livro), 1, lista_l);
    fclose(lista_l);
}

char livro [50];
int i;

void p_livros() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    struct Livro l;
    printf("Digite o livro que deseja procurar: ");
    scanf(" %[^\n]", livro);

    //Converte a string digitada para minusculo
    for(i = 0; livro[i] != '\0'; i++){
        if(livro[i] >= 'A' && livro[i] <= 'Z'){
            livro[i] = livro[i] + 32;
        }
    }
    lista_l = fopen ("../data/ListaLivros.txt", "rb");

    if(lista_l == NULL){
        printf("\nErro inesperado!\n");
        system("pause");
        exit(1);
    }
    while(!feof(lista_l)){
        fread(&l, sizeof(struct Livro), 1, lista_l);
        if(feof(lista_l))
            break;

        //Converte o nome do livro no arq para minusculo
        for(i = 0; l.nome[i] != '\0'; i++){
            if(l.nome[i] >= 'A' && l.nome[i] <= 'Z'){
                l.nome[i] = l.nome[i] + 32;
            }
        }


        for(i=0; livro[i] != '\0' && l.nome[i] != '\0'; i++){
            if(livro[i] != l.nome[i]){
                break;
            }
            
        }
        if(livro[i] == '\0' && l.nome[i] == '\0'){
            printf("O livro está no sistema!\n");
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
    if(livro[i] != '\0' && l.nome[i] != '\0')
        printf("Livro nao esta cadastrado no sistema");
    fclose(lista_l);
    
}