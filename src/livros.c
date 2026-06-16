#include "../include/livros.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void c_livros()
{
    FILE *lista_l = fopen("data/ListaLivros.txt", "ab");

    if (lista_l == NULL)
    {
        printf("\nErro inesperado ao abrir o arquivo!\n");
        pausar();
        return;
    }
    int n, i;

    exibirTitulo("assets/livros.txt");
    printf("\n");
    printf("Quantos livros deseja cadastrar?: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        erroEntrada("Quantidade inválida!");
        fclose(lista_l);
        return;
    }
    limparBuffer();

    struct Livro *l = malloc(n * sizeof(struct Livro));

    if (l == NULL)
    {
        printf("Erro de alocação!\n");
        fclose(lista_l);
        pausar();
        return;
    }

    // Randomizador de ID (7 Algarismos)
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        l[i].id = 1000000 + rand() % 9000000;

        // Entrada dos dados pelo usuário.
        printf("\nDigite o Nome do livro que queira cadastrar: ");
        scanf(" %[^\n]", l[i].nome);
        limparBuffer();

        printf("Digite o Nome do Autor(a): ");
        scanf(" %[^\n]", l[i].autor);
        limparBuffer();

        printf("Digite o gênero do livro: ");
        scanf(" %[^\n]", l[i].genero);
        limparBuffer();

        printf("Digite o ano de publicação (usando números): ");
        if (scanf("%d", &l[i].ano) != 1)
        {
            l[i].ano = 0;
        }
        limparBuffer();

        printf("Digite a quantidade total do livro: ");
        if (scanf("%d", &l[i].quant_total) != 1)
        {
            l[i].quant_total = 0;
        }
        limparBuffer();

        l[i].quant_emprestado = 0;
        l[i].v_emp = 0;
        l[i].quant_disp = l[i].quant_total - l[i].quant_emprestado;

        printf("\n--- Livro Cadastrado ---\n");
        printf("O ID do seu livro será: %d\n", l[i].id);
        printf("A quantidade disponível é: %d\n", l[i].quant_disp);
        printf("---------------------\n");
    }

    fwrite(l, sizeof(struct Livro), n, lista_l);

    free(l);
    l = NULL;
    fclose(lista_l);

    printf("\nLivro(s) cadastrado(s) com sucesso!\n");
    pausar();
}

void p_livros()
{
    char livro[50];
    struct Livro l;
    int pesq, i, j;
    int id_livro;
    int encontrado = 0;

    FILE *lista_l = fopen("data/ListaLivros.txt", "rb");
    if (lista_l == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    exibirTitulo("assets/livros.txt");
    printf("\n");
    printf("(1) Pesquisa por nome.\n");
    printf("(2) Pesquisa por ID.\n");
    printf("\n");

    printf("Selecione a opção que você deseja: ");
    if (scanf("%d", &pesq) != 1)
    {
        limparBuffer();
        fclose(lista_l);
        erroEntrada("Resposta inválida!");
        return;
    }
    limparBuffer();

    switch (pesq)
    {
    case 1:
        printf("\nDigite o nome do livro que deseja procurar: ");
        scanf(" %[^\n]", livro);
        limparBuffer();

        // Converte o livro buscado para minúsculo
        for (i = 0; livro[i] != '\0'; i++)
        {
            if (livro[i] >= 'A' && livro[i] <= 'Z')
                livro[i] = livro[i] + 32;
        }

        while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
        {
            char temp[50];
            strcpy(temp, l.nome);

            // Converte temp para minúsculo
            for (j = 0; temp[j] != '\0'; j++)
            {
                if (temp[j] >= 'A' && temp[j] <= 'Z')
                    temp[j] = temp[j] + 32;
            }

            if (strstr(temp, livro) != NULL)
            {
                encontrado = 1;
                printf("\n");
                printf("O livro está no sistema!\n");
                printf("\n");
                printf("ID: %d\n", l.id);
                printf("Nome: %s\n", l.nome);
                printf("Autor: %s\n", l.autor);
                printf("Gênero: %s\n", l.genero);
                printf("Ano: %d\n", l.ano);
                printf("Qtd. total: %d\n", l.quant_total);
                printf("Qtd. emprestado: %d\n", l.quant_emprestado);
                printf("Disponíveis: %d\n", l.quant_disp);
            }
        }

        if (!encontrado)
            printf("\nLivro não está cadastrado no sistema.\n");
        break;

    case 2:
        printf("\nDigite o ID do livro que deseja buscar (7 algarismos): ");
        if (scanf("%d", &id_livro) != 1)
        {
            printf("\nID inválido! Digite apenas números.\n");
            limparBuffer();
            break;
        }
        limparBuffer();

        while (fread(&l, sizeof(struct Livro), 1, lista_l) == 1)
        {
            if (l.id == id_livro)
            {
                encontrado = 1;
                printf("\n");
                printf("O livro está no sistema!\n");
                printf("\n");
                printf("ID: %d\n", l.id);
                printf("Nome: %s\n", l.nome);
                printf("Autor: %s\n", l.autor);
                printf("Gênero: %s\n", l.genero);
                printf("Ano: %d\n", l.ano);
                printf("Qtd. total: %d\n", l.quant_total);
                printf("Qtd. emprestado: %d\n", l.quant_emprestado);
                printf("Disponíveis: %d\n", l.quant_disp);
                break;
            }
        }
        if (!encontrado)
            printf("\nLivro não está cadastrado no sistema.\n");
        break;

    default:
        erroEntrada("Opção inválida!");
        fclose(lista_l);
        return;
    }

    fclose(lista_l);
    pausar();
    limparTela();
}

void r_livros()
{
    int id_r;
    int encontrado = 0;
    int impedido = 0;
    struct Livro l;

    printf("Digite o ID do livro que deseja remover: ");
    if (scanf("%d", &id_r) != 1)
    {
        printf("\nID inválido! Digite apenas números.\n");
        limparBuffer();
        pausar();
        return;
    }
    limparBuffer();

    FILE *lista_ori = fopen("data/ListaLivros.txt", "rb");
    if (lista_ori == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    FILE *lista_t = fopen("data/temp.txt", "wb");
    if (lista_t == NULL)
    {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(lista_ori);
        pausar();
        return;
    }

    while (fread(&l, sizeof(struct Livro), 1, lista_ori) == 1)
    {
        if (l.id != id_r)
        {
            fwrite(&l, sizeof(struct Livro), 1, lista_t);
        }
        else
        {
            encontrado = 1;
            if (l.quant_emprestado > 0)
            {
                impedido = 1;
                printf("\nNão é possível remover '%s', pois há %d empréstimo(s) ativo(s)!\n", l.nome, l.quant_emprestado);
                fwrite(&l, sizeof(struct Livro), 1, lista_t);
            }
            else
            {
                printf("\nLivro '%s' removido com sucesso!\n", l.nome);
            }
        }
    }

    fclose(lista_ori);
    fclose(lista_t);

    if (!encontrado)
    {
        printf("\nLivro não encontrado!\n");
        remove("data/temp.txt");
        pausar();
        return;
    }

    if (impedido)
    {
        remove("data/temp.txt");
        pausar();
        return;
    }

    remove("data/ListaLivros.txt");
    rename("data/temp.txt", "data/ListaLivros.txt");
    pausar();
}

void l_livros()
{
    struct Livro l;
    int i = 0;

    FILE *lista_l = fopen("data/ListaLivros.txt", "rb");
    if (lista_l == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    while (fread(&l, sizeof(struct Livro), 1, lista_l))
    {
        printf("Livro %d--> ", i + 1);
        printf("ID: %d || ", l.id);
        printf("Nome: %s || ", l.nome);
        printf("Autor: %s || ", l.autor);
        printf("Gênero: %s || ", l.genero);
        printf("Ano: %d || ", l.ano);
        printf("Qtd. Total: %d || ", l.quant_total);
        printf("Qtd. Disp: %d || ", l.quant_disp);
        printf("Qtd. Emprestada: %d ||\n", l.quant_emprestado);
        i++;
    }
    printf("\n↑↑↑ Total de livros: %d ↑↑↑\n", i);

    fclose(lista_l);
    pausar();
    limparBuffer();
    limparTela();
}

void a_livros()
{
    int id_att, pesq;
    int encontrado = 0;
    int cancelar_alteracao = 0;
    struct Livro l;

    printf("Digite o ID do livro que deseja atualizar: ");
    if (scanf("%d", &id_att) != 1)
    {
        printf("\nID inválido! Digite apenas números.\n");
        limparBuffer();
        pausar();
        return;
    }
    limparBuffer();

    FILE *lista_ori = fopen("data/ListaLivros.txt", "rb");
    if (lista_ori == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    FILE *lista_t = fopen("data/temp.txt", "wb");
    if (lista_t == NULL)
    {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(lista_ori);
        pausar();
        return;
    }

    while (fread(&l, sizeof(struct Livro), 1, lista_ori) == 1)
    {
        if (id_att == l.id)
        {
            encontrado = 1;
            printf("\nLivro: %s\n", l.nome);
            printf("( 1 ) Nome\n");
            printf("( 2 ) Autor\n");
            printf("( 3 ) Gênero\n");
            printf("( 4 ) Ano\n");
            printf("( 5 ) Qtd. Total\n");
            printf("( 0 ) Retornar\n");

            printf("Qual dado deseja alterar?: ");
            if (scanf("%d", &pesq) != 1)
            {
                pesq = -1;
            }
            limparBuffer();

            char temp[50];
            int t;
            switch (pesq)
            {
            case 0:
                cancelar_alteracao = 1;
                break;

            case 1:
                printf("Nome atual: %s\n", l.nome);
                printf("Se quiser manter o atual pressione Enter...\n");
                printf("Se quiser modificar, escreva o novo nome: ");
                fgets(temp, 50, stdin);
                temp[strcspn(temp, "\n")] = '\0';
                if (temp[0] != '\0')
                    strcpy(l.nome, temp);
                break;

            case 2:
                printf("Autor atual: %s\n", l.autor);
                printf("Se quiser manter o atual pressione Enter...\n");
                printf("Se quiser modificar, escreva o novo autor: ");
                fgets(temp, 50, stdin);
                temp[strcspn(temp, "\n")] = '\0';
                if (temp[0] != '\0')
                    strcpy(l.autor, temp);
                break;

            case 3:
                printf("Gênero atual: %s\n", l.genero);
                printf("Se quiser manter o atual pressione Enter...\n");
                printf("Se quiser modificar, escreva o novo Gênero: ");
                fgets(temp, 50, stdin);
                temp[strcspn(temp, "\n")] = '\0';
                if (temp[0] != '\0')
                    strcpy(l.genero, temp);
                break;

            case 4:
                printf("Ano atual: %d\n", l.ano);
                printf("Se quiser manter o atual, Digite 0 e pressione Enter...\n");
                printf("Se quiser modificar, escreva o novo ano: ");
                if (scanf("%d", &t) == 1 && t != 0)
                {
                    l.ano = t;
                }
                limparBuffer();
                break;

            case 5:
                printf("Qtd. Total atual: %d\n", l.quant_total);
                printf("Se quiser manter o atual, Digite 0 e pressione Enter...\n");
                printf("Se quiser modificar, escreva a nova Qtd. Total: ");
                if (scanf("%d", &t) == 1 && t != 0)
                {
                    l.quant_total = t;
                    l.quant_disp = l.quant_total - l.quant_emprestado;
                }
                limparBuffer();
                break;

            default:
                printf("Opção inválida!\n");
                break;
            }
            if (!cancelar_alteracao && pesq >= 1 && pesq <= 5)
            {
                printf("\n--- Cadastro atualizado ---\n");
            }
        }
        fwrite(&l, sizeof(struct Livro), 1, lista_t);
    }

    fclose(lista_ori);
    fclose(lista_t);

    if (cancelar_alteracao)
    {
        printf("\nOperação cancelada pelo usuário.\n");
        remove("data/temp.txt");
        pausar();
        return;
    }

    if (!encontrado)
    {
        printf("Livro não encontrado!\n");
        remove("data/temp.txt");
        pausar();
        return;
    }

    remove("data/ListaLivros.txt");
    rename("data/temp.txt", "data/ListaLivros.txt");
    pausar();
}


/*void e_livros() 
{
    int id_busca;
    struct Emprestimo e;
    struct Usuario u;
    int encontrado = 0;

    printf("Digite o ID do livro: ");
    scanf("%d", &id_busca);
    limparBuffer();

    FILE *arq_e = fopen("data/ListaEmprestimos.txt", "rb");
    if(arq_e == NULL){
        printf("Erro na abertura do arquivo!\n");
        system("pause");
        return;
    }

    printf("\n<--- EMPRESTIMOS DO LIVRO --->\n");
    while(fread(&e, sizeof(struct Emprestimo), 1, arq_e) == 1){
        if(e.id == id_busca && e.devolvido == 0){
            encontrado = 1;

            //busca e exibe o nome do usuário
            FILE *arq_u = fopen("data/ListaUsuarios.txt", "rb");
            while(fread(&u, sizeof(struct Usuario), 1, arq_u) == 1){
                if(u.matricula == e.matricula_usuario){
                    printf("Usuario:    %s\n", u.nome);
                    printf("Matricula:  %d\n", u.matricula);
                    break;
                }
            }
            fclose(arq_u);

            printf("Emprestado em: %02d/%02d/%d\n", e.data_emprestimo[0], e.data_emprestimo[1], e.data_emprestimo[2]);
            printf("Devolucao em:  %02d/%02d/%d\n\n", e.data_devolucao[0], e.data_devolucao[1], e.data_devolucao[2]);
        }
    }
    fclose(arq_e);

    // ✅ caso não haja empréstimos ativos
    if(!encontrado)
        printf("Este livro nao possui emprestimos ativos.\n");

    pausar();
}*/
