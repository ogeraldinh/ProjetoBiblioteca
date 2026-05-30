#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "menu.h"

int main () {
    FILE *logo;
    int resposta;
    char linha[50];

    setlocale(LC_ALL, "pt_BR.UTF-8");

    logo = fopen("../data/logo.txt", "r");

   while (1) { 
        printf("\n");
        logo = fopen("../data/logo.txt", "r");
        while(fgets(linha, 50, logo)){
            printf("%s", linha);
        }
        printf("( 1 ) Pesquisar Livros \n");
        printf("( 2 ) Cadastrar Livros \n");
        printf("( 3 ) Pesquisar Usuários \n");
        printf("( 4 ) Cadastrar Usuário \n");
        printf("( 5 ) Gerar relatório \n");
        printf("( 0 ) Encerrar o programa \n");
        printf("Selecione a opcao que voce deseja: ");

        if(!scanf("%d", &resposta)){
            printf("Entrada invalida. Digite um numero!\n");
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }

        switch (resposta){
            case 0:
                printf("Encerrando...");
                printf("\n");
                return 0; 
            case 1:
                printf("\n");              
                printf("pesquisando livros...");
                printf("\n");
                p_livros();
                break;  
            case 2:
                printf("\n");
                printf("Cadastrando livros...");
                printf("\n");
                c_livros();
                break;  
            case 3:
                printf("\n");
                printf("Pesquisando usuário...");
                printf("\n");
                break;  
            case 4:
                printf("\n");
                printf("Cadastrando usuário...");
                printf("\n");
                break;  
            case 5:
                printf("\n");
                printf("Gerando relatório...\n");
                printf("\n");
                break;    
            default:
                printf("Opcao invalida! Tente novamente.");
                printf("\nPressione Enter para continuar...");

                getchar();
                break;
        }
    }

    return 0;
}