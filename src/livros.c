#include <stdio.h>
#include <stdlib.h>
#include <menu.h>
FILE *lista_l;
struct Cadastro{
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
    lista_l = fopen("../data/ListaLivros.txt", "a");

    if(lista_l == NULL){
        printf("\nErro inesperado!\n");
        system("pause");
        exit(1);
    }

    struct Cadastro l;
    //Randomizador de ID (7 Algorismos)
    l.id = 1000000 + rand() % 9000000;
    //Entrada dos dados pela usuário.
    printf("Digite o Nome do livro que queira cadastrar: ");
    gets(l.nome);
    printf("Digite o Nome do Autor(a): ");
    gets(l.autor);
    printf("Digite o gênero do livro: ");
    gets(l.genero);
    printf("Digite o ano de publicação(usando números): ");
    gets(l.ano);
    printf("Digite a quantidade total do livro: ");
    gets(l.quant_total);
    printf("Digite o Nome do livro que queira cadastrar: ");
    gets(l.quant_emprestado);
    l.quant_disp = l.quant_total - l.quant_emprestado;
    printf("A quantidade disponível é %d", l.quant_disp);

    fprintf(lista_l,"id: %d\n", l.id);
    fprintf(lista_l,"Nome: %s\n", l.nome);
    fprintf(lista_l,"Autor: %s\n", l.autor);
    fprintf(lista_l,"Gênero: %s\n", l.genero);
    fprintf(lista_l,"Ano de publicação: %d\n", l.ano);
    fprintf(lista_l,"Qtd. total: %d\n", l.quant_total);
    fprintf(lista_l,"Qtd. emprestado: %d\n", l.quant_emprestado);
    fprintf(lista_l,"Disponíveis: %d\n", l.quant_disp);
    fprintf(lista_l,"<----------------------------------------------->");
    fclose(lista_l);

}

char livro [50];
char leitor [50];
int i, j;

void p_livros() {
    printf("Digite o livro que deseja procurar: ");
    gets(livro);
    lista_l = fopen ("../data/ListaLivros.txt", "r");

    if(lista_l == NULL){
        printf("\nErro inesperado!\n");
        system("pause");
        exit(1);
    }
    while(fgets(leitor, sizeof(leitor), lista_l) != NULL){
        for (i=0; i < sizeof(livro); i++){
            if(livro[i] == leitor[j])
            j++;

        }
    }
    if(livro[i] == leitor[j]){
        printf("%s está no sistema!", livro);
        //printf id
        //printf autor
        //printf disponibilidade
        //printf ano de publicação 
        //printf gênero
    }

}