#include "../include/usuarios.h"
#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void c_usuarios()
{
    FILE *lista_u = fopen("data/ListaUsuarios.txt", "ab");

    if (lista_u == NULL)
    {
        printf("\nErro inesperado ao abrir o arquivo!\n");
        pausar();
        return;
    }
    int n, i;
    printf("Quantos usuários deseja cadastrar?: ");
    scanf("%d", &n);
    struct Usuario *u = malloc(n * sizeof(struct Usuario));

    if (u == NULL)
    {
        printf("Erro de alocacao!\n");
        fclose(lista_u);
        pausar();
        return;
    }

    // Randomizador de Matrícula (7 Algorismos)
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        u[i].matricula = 1000000 + rand() % 9000000;
        // Entrada dos dados pelo usuário.
        printf("Digite o nome do discente: ");
        scanf(" %[^\n]", u[i].nome);
        printf("Digite o curso do discente: ");
        scanf(" %[^\n]", u[i].curso);
        u[i].quant_emprestimos_ativos = 0;
    }

    fwrite(u, sizeof(struct Usuario), n, lista_u);
    free(u);
    u = NULL;
    fclose(lista_u);
    pausar();
}

void p_usuarios()
{
    char usuario[50];

    struct Usuario u;
    int pesq, i, j;
    int matricula_usuario;
    int encontrado = 0;

    FILE *lista_u = fopen("data/ListaUsuarios.txt", "rb");
    if (lista_u == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }
    printf("\n");
    exibirTitulo("assets/usuarios.txt");
    printf("--------------------------------------------");
    printf("\n");
    printf("(1) Pesquisa por nome.\n");
    printf("(2) Pesquisa por matrícula.\n");
    printf("\n");

    printf("Selecione a opção que você deseja: ");
    scanf("%d", &pesq);
    switch (pesq)
    {
    case 1:

        printf("\nDigite o nome que deseja procurar: ");
        scanf(" %[^\n]", usuario);

        // Converte o usuário buscado para minúsculo
        for (i = 0; usuario[i] != '\0'; i++)
        {
            if (usuario[i] >= 'A' && usuario[i] <= 'Z')
                usuario[i] = usuario[i] + 32;
        }
        while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        {
            // temp para copiar o usuário no arquivo e passar para minúsculo
            char temp[50];
            strcpy(temp, u.nome);

            // Converte temp para minúsculo (não modifica o arquivo)
            for (j = 0; temp[j] != '\0'; j++)
                if (temp[j] >= 'A' && temp[j] <= 'Z')
                    temp[j] = temp[j] + 32;

            if (strcmp(usuario, temp) == 0)
            {
                encontrado = 1;
                printf("\n");
                printf("Usuário encontrado.\n");
                printf("\n");
                printf("Nome: %s\n", u.nome);
                printf("Curso: %s\n", u.curso);
                printf("Matrícula: %d\n", u.matricula);
                printf("Empréstimos ativos: %d\n", u.quant_emprestimos_ativos);
                break;
            }
        }

        if (!encontrado)
            fclose(lista_u);
        break;

    case 2:
        // Entrada de dados da matrícula
        printf("\nDigite a matrícula do usuário que deseja buscar (7 algarismos): ");
        scanf("%d", &matricula_usuario);

        // Enquanto fread não achar ou chegar ao EOF
        while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        {
            if (u.matricula == matricula_usuario)
            {
                encontrado = 1;
                printf("\n");
                printf("Usuário encontrado.\n");
                printf("\n");
                printf("Nome: %s\n", u.nome);
                printf("Curso: %s\n", u.curso);
                printf("Matrícula: %d\n", u.matricula);
                printf("Empréstimos ativos: %d\n", u.quant_emprestimos_ativos);
                break;
            }
        }
        if (!encontrado)
            printf("Usuário não está cadastrado no sistema!\n");
        break;
    default:
        erroEntrada("Opção inválida!");
        return;
    }
    fclose(lista_u);
    limparBuffer();
    pausar();
    limparTela();
}

void r_usuarios()
{

    int matricula_r;
    int encontrado = 0;
    struct Usuario u;

    printf("Digite a Matrícula do usuário que deseja remover: ");
    scanf("%d", &matricula_r);

    // abrir original para ReadB
    FILE *lista_ori = fopen("data/ListaUsuarios.txt", "rb");
    if (lista_ori == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    // abrir um temporario para WriteB
    FILE *lista_t = fopen("data/temp.txt", "wb");
    if (lista_t == NULL)
    {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(lista_ori);
        pausar();
        return;
    }

    // acha o usuário que vai ser removido e não copia no temp
    while (fread(&u, sizeof(struct Usuario), 1, lista_ori) == 1)
    {
        if (u.matricula != matricula_r)
        {
            fwrite(&u, sizeof(struct Usuario), 1, lista_t);
        }
        else
        {
            encontrado = 1;
            printf("Usuário '%s' removido com sucesso!\n", u.nome);
        }
    }

    fclose(lista_ori);
    fclose(lista_t);

    if (!encontrado)
    {
        printf("Usuário não encontrado!\n");
        // se matrícula não encontrada cancela a temp e não altera a original
        remove("data/temp.txt");
        pausar();
        return;
    }

    // remove o original e dá rename na temp para nova original
    remove("data/ListaUsuarios.txt");
    rename("data/temp.txt", "data/ListaUsuarios.txt");
    pausar();
}

void l_usuarios()
{

    struct Usuario u;
    int i = 0;

    FILE *lista_u = fopen("data/ListaLivros.txt", "rb");
    if (lista_u == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }
    while (fread(&u, sizeof(struct Usuario), 1, lista_u))
    {
        printf("Usuáro %d--> ", i + 1);
        printf("Nome: %s|| ", u.nome);
        printf("Matrícula: %d|| ", u.matricula);
        printf("Ano: %s|| ", u.curso);
        printf("Empréstimos ativos: %d||\n", u.quant_emprestimos_ativos);
        i++;
    }
    printf("\n↑↑↑ Total de usuários: %d ↑↑↑\n", i);
    fclose(lista_u);
    pausar();
}

void a_usuarios()
{

    int matricula_att, pesq;
    int encontrado = 0;
    struct Usuario u;

    printf("Digite a matrícula do livro que deseja atualizar: ");
    scanf("%d", &matricula_att);

    FILE *lista_ori = fopen("data/ListaUsuarios.txt", "rb");
    if (lista_ori == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    FILE *lista_t = fopen("data/temp.txt", "wb");
    if (lista_t == NULL)
    {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(lista_ori);
        pausar();
        return;
    }

    while (fread(&u, sizeof(struct Usuario), 1, lista_ori) == 1)
    {
        if (matricula_att == u.matricula)
        {
            encontrado = 1;
            printf("Nome: %s\n", u.nome);
            printf("Matrícula: %d\n", u.matricula);
            printf("( 1 ) Nome\n");
            printf("( 2 ) Curso\n");
            printf("( 0 ) Retornar\n");
            printf("Qual dado deseja alterar?: ");
            scanf("%d", &pesq);
            limparBuffer();
            char temp[50];
            switch (pesq)
            {
            case 0:
                fclose(lista_ori);
                fclose(lista_t);
                remove("data/temp.txt");
                return;

            case 1:
                printf("Nome: %s\n", u.nome);
                printf("Se quiser manter o atual pressione Enter...\n");
                printf("Se quiser modificar, escreva o novo nome: ");
                fgets(temp, 50, stdin);
                temp[strcspn(temp, "\n")] = '\0';
                if (temp[0] != '\0')
                    strcpy(u.nome, temp);

                break;

            case 2:
                printf("Autor: %s\n", u.curso);
                printf("Se quiser manter o atual pressione Enter...\n");
                printf("Se quiser modificar, escreva o novo autor: ");
                fgets(temp, 50, stdin);
                temp[strcspn(temp, "\n")] = '\0';
                if (temp[0] != '\0')
                    strcpy(u.curso, temp);
                break;

            default:
                printf("Opcao invalida!\n");
                break;
            }
            printf("--- Cadastro atualizado ---\n");
        }
        fwrite(&u, sizeof(struct Usuario), 1, lista_t);
    }

    fclose(lista_ori);
    fclose(lista_t);

    if (!encontrado)
    {
        printf("Livro nao encontrado!\n");
        remove("data/temp.txt");
        pausar();
        return;
    }

    remove("data/ListaLivros.txt");
    rename("data/temp.txt", "data/ListaLivros.txt");
    pausar();
}