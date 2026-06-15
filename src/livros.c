#include "../include/livros.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

void c_livros() {
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


                if(strstr(temp, livro) != 0){
                    encontrado = 1;
                    printf("<-------------------------------->\n");
                    printf("O livro esta no sistema!\n");
                    printf("ID: %d\n", l.id);
                    printf("Nome: %s\n", l.nome);
                    printf("Autor: %s\n", l.autor);
                    printf("Genero: %s\n", l.genero);
                    printf("Ano: %d\n", l.ano);
                    printf("Qtd. total: %d\n", l.quant_total);
                    printf("Qtd. emprestado: %d\n", l.quant_emprestado);
                    printf("Disponiveis: %d\n", l.quant_disp);
                    printf("<-------------------------------->\n");
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
        } else if(l.quant_emprestado > 0){
                    //não remove se houver emprestimos
                    encontrado = 1;
                    printf("Nao e possivel remover %s. Pois ha %d emprestimos!!!!\n", l.nome, l.quant_emprestado);
                    fwrite(&l, sizeof(struct Livro), 1, lista_t);
                } else {
                    printf("Livro %s removido!!!!\n", l.nome);
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

void l_livros() {

    struct Livro l;
    int i = 0;

    FILE *lista_l = fopen("data/ListaLivros.txt", "rb");
    if(lista_l == NULL){
        printf("Erro ao abrir arquivo!\n");
        system("pause");
        return;
    }
    while(fread(&l, sizeof(struct Livro), 1, lista_l)){
        printf("Livro %d--> ", i+1);
        printf("ID: %d|| ", l.id);
        printf("Nome: %s|| ", l.nome);
        printf("Autor: %s|| ", l.autor);
        printf("Genero: %s|| ", l.genero);
        printf("Ano: %d|| ", l.ano);
        printf("Qtd.total: %d|| ", l.quant_total);
        printf("Qtd.disp: %d|| ", l.quant_disp);
        printf("Qtd.Empres: %d||\n", l.quant_emprestado);
        i++;
    }
    printf("\n↑↑↑ Total de livros: %d ↑↑↑\n", i);
    fclose(lista_l);
    system("pause");
}

void a_livros() {

    int id_att, pesq;
    int encontrado = 0;
    struct Livro l;

    printf("Digite o ID do livro que deseja atualizar: ");
    scanf("%d", &id_att);

    FILE *lista_ori = fopen("data/ListaLivros.txt", "rb");
    if(lista_ori == NULL){
        printf("Erro ao abrir arquivo!\n");
        system("pause");
        return;
    }

    FILE *lista_t = fopen("data/temp.txt", "wb");
    if(lista_t == NULL){
        printf("Erro ao criar arquivo temporario!\n");
        fclose(lista_ori);
        system("pause");
        return;
    }

    while(fread(&l, sizeof(struct Livro), 1, lista_ori) == 1){
        if(id_att == l.id){
            encontrado = 1;
            printf("Livro: %s\n", l.nome);
            printf("( 1 ) Nome\n");
            printf("( 2 ) Autor\n");
            printf("( 3 ) Genero\n");
            printf("( 4 ) Ano\n");
            printf("( 5 ) Qtd.Total\n");
            printf("( 0 ) Retornar\n");
            printf("Qual dado deseja alterar?: ");
            scanf("%d", &pesq);
            limparBuffer();
            char temp[50];
            int t;
            switch(pesq){
                case 0:
                    fclose(lista_ori);
                    fclose(lista_t);
                    remove("data/temp.txt");
                    return;


                case 1:
                    printf("Nome: %s\n", l.nome);
                    printf("Se quiser manter o atual pressione Enter...\n");
                    printf("Se quiser modificar, escreva o novo nome: ");
                    fgets(temp, 50, stdin);
                    temp[strcspn(temp, "\n")] = '\0';
                    if(temp[0] != '\0')
                        strcpy(l.nome, temp);

                    break;

                case 2:
                    printf("Autor: %s\n", l.autor);
                    printf("Se quiser manter o atual pressione Enter...\n");
                    printf("Se quiser modificar, escreva o novo autor: ");
                    fgets(temp, 50, stdin);
                    temp[strcspn(temp, "\n")] = '\0';
                    if(temp[0] != '\0')
                        strcpy(l.autor, temp);
                    break;

                case 3:
                    printf("Genero: %s\n", l.genero);
                    printf("Se quiser manter o atual pressione Enter...\n");
                    printf("Se quiser modificar, escreva o novo Genero: ");
                    fgets(temp, 50, stdin);
                    temp[strcspn(temp, "\n")] = '\0';

                    if(temp[0] != '\0')
                        strcpy(l.genero, temp);
                    break;

                case 4:
                    printf("Ano: %d\n", l.ano);
                    printf("Se quiser manter o atual, Digite 0 e pressione Enter...\n");
                    printf("Se quiser modificar, escreva o novo ano: ");
                    scanf("%d", &t);
                    if(t != 0)
                        l.ano = t;
                    break;

                case 5:
                    printf("Qtd.Total: %d\n", l.quant_total);
                    printf("Se quiser manter o atual, Digite 0 e pressione Enter...\n");
                    printf("Se quiser modificar, escreva a nova Qtd.Total: ");
                    scanf("%d", &t);
                    if(t != 0){
                        l.quant_total = t;
                        l.quant_disp = (l.quant_total - l.quant_emprestado);
                    }
                    break;

                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            printf("<--- Livro Atualizado! --->\n");

        }
        fwrite(&l, sizeof(struct Livro), 1, lista_t);
    }
    fclose(lista_ori);
    fclose(lista_t);

    if(!encontrado){
        printf("Livro nao encontrado!\n");
        remove("data/temp.txt");
        system("pause");
        return;
    }

    remove("data/ListaLivros.txt");
    rename("data/temp.txt", "data/ListaLivros.txt");
    system("pause");
}