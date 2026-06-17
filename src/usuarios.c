// Bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Módulos Locais
#include "../include/usuarios.h"
#include "../include/auxiliares.h"

// Função de execução do menu principal
void c_usuarios()
{
    FILE *lista_u = fopen("data/ListaUsuarios.dat", "a+b");

    if (lista_u == NULL)
    {
        printf("\nErro inesperado ao abrir o arquivo!\n");
        pausar();
        return;
    }
    int n, i;

    exibirTitulo("assets/usuarios.txt");
    printf("\n");
    printf("Quantos usuários deseja cadastrar?: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        erroEntrada("Quantidade inválida!");
        limparBuffer();
        fclose(lista_u);
        return;
    }

    limparBuffer();

    struct Usuario *u = malloc(n * sizeof(struct Usuario));

    if (u == NULL)
    {
        printf("Erro de alocação!\n");
        fclose(lista_u);
        pausar();
        return;
    }

    // Randomizador de Matrícula (5 Algorismos) fora do FOR para nao gerar numeros iguais
    srand(time(NULL));
    int verificar;
    struct Usuario t;
    for (i = 0; i < n; i++)
    {
        do
        {
            verificar = 0;

            u[i].matricula = 10000 + rand() % 90000;

            // verifica se o ID dos livros sendo cadastrados AGORA são iguais
            for (int j = 0; j < i; j++)
            {
                if (u[i].matricula == u[j].matricula)
                {
                    verificar = 1;
                    break;
                }
            }

            if (verificar)
                continue;

            rewind(lista_u);

            while (fread(&t, sizeof(struct Usuario), 1, lista_u) == 1)
            {
                if (u[i].matricula == t.matricula)
                {
                    verificar = 1;
                    break;
                }
            }

        } while (verificar);

        // Entrada dos dados pelo usuário.
        printf("Digite o nome do discente: ");
        scanf(" %[^\n]", u[i].nome);
        limparBuffer();

        printf("Digite o curso do discente: ");
        scanf(" %[^\n]", u[i].curso);
        limparBuffer();

        u[i].quant_emprestimos_ativos = 0;
    }

    fwrite(u, sizeof(struct Usuario), n, lista_u);

    free(u);
    u = NULL;
    fclose(lista_u);

    printf("\nUsuário(s) cadastrado(s) com sucesso!\n");
    pausar();
}

// Função de execução do menu principal
void p_usuarios()
{
    char usuario[50];

    struct Usuario u;
    int pesq, i, j;
    int matricula_usuario;
    int encontrado = 0;

    FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb");
    if (lista_u == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    exibirTitulo("assets/usuarios.txt");
    printf("\n");
    printf("(1) Pesquisa por nome.\n");
    printf("(2) Pesquisa por matrícula.\n");
    printf("(0) Retornar.\n");
    printf("\n");

    printf("Selecione a opção que você deseja: ");

    if (scanf("%d", &pesq) != 1)
    {
        limparBuffer();
        fclose(lista_u);
        erroEntrada("Resposta inválida!");
        return;
    }

    limparBuffer();

    switch (pesq)
    {
    case 0:
        limparTela();
        return;

    case 1:

        printf("\nDigite o nome que deseja procurar: ");
        scanf(" %[^\n]", usuario);
        limparBuffer();

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
                printf("=====================================================\n");
                printf("Nome              : %s\n", u.nome);
                printf("Curso             : %s\n", u.curso);
                printf("Matrícula         : %d\n", u.matricula);
                printf("Empréstimos ativos: %d\n", u.quant_emprestimos_ativos);
                printf("=====================================================\n");
                break;
            }
        }

        if (!encontrado)
            printf("Usuário não está cadastrado no sistema!\n");
        break;

    case 2:
        // Entrada de dados da matrícula
        printf("\nDigite a matrícula do usuário que deseja buscar (7 algarismos): ");

        if (scanf("%d", &matricula_usuario) != 1)
        {
            printf("\nMatrícula inválida! Digite apenas números.\n");
            limparBuffer();
            break;
        }

        limparBuffer();

        // Enquanto fread não achar ou chegar ao EOF
        while (fread(&u, sizeof(struct Usuario), 1, lista_u) == 1)
        {
            if (u.matricula == matricula_usuario)
            {
                encontrado = 1;
                printf("\n");
                printf("Usuário encontrado.\n");
                printf("\n");
                printf("=====================================================\n");
                printf("Nome              : %s\n", u.nome);
                printf("Curso             : %s\n", u.curso);
                printf("Matrícula         : %d\n", u.matricula);
                printf("Empréstimos ativos: %d\n", u.quant_emprestimos_ativos);
                printf("=====================================================\n");
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
    pausar();
    limparTela();
}

// Função para remover usuários
void r_usuarios()
{
    int matricula_r;
    int encontrado = 0;
    struct Usuario u;

    printf("Digite a Matrícula do usuário que deseja remover: ");

    if (scanf("%d", &matricula_r) != 1)
    {
        printf("\nMatrícula inválida! Digite apenas números.\n");
        limparBuffer();
        return;
    }

    limparBuffer();

    FILE *lista_ori = fopen("data/ListaUsuarios.dat", "rb");

    if (lista_ori == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }

    // procura usuário
    while (fread(&u, sizeof(struct Usuario), 1, lista_ori) == 1)
    {
        if (u.matricula == matricula_r)
        {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Usuário não encontrado!\n");

        fclose(lista_ori);
        pausar();
        limparTela();
        return;
    }

    if (u.quant_emprestimos_ativos > 0)
    {
        printf("\nNão é possível remover usuário com empréstimos ativos!\n");

        fclose(lista_ori);
        pausar();
        limparTela();
        return;
    }

    printf("\nUsuário encontrado:\n");
    printf("Nome: %s\n", u.nome);
    printf("Curso: %s\n", u.curso);
    printf("Matrícula: %d\n", u.matricula);

    if (!confirmar("\nConfirmar realização da exclusão?"))
    {
        printf("Ação cancelada!\n");

        fclose(lista_ori);
        pausar();
        limparTela();
        return;
    }

    fclose(lista_ori);

    // reabre para recriar o arquivo
    lista_ori = fopen("data/ListaUsuarios.dat", "rb");

    FILE *lista_t = fopen("data/temp.txt", "wb");
    if (lista_t == NULL)
    {
        printf("Erro ao criar arquivo temporário!\n");

        fclose(lista_ori);
        pausar();
        return;
    }

    while (fread(&u, sizeof(struct Usuario), 1, lista_ori) == 1)
    {
        if (u.matricula != matricula_r)
        {
            fwrite(&u, sizeof(struct Usuario), 1, lista_t);
        }
    }

    fclose(lista_ori);
    fclose(lista_t);

    remove("data/ListaUsuarios.dat");
    rename("data/temp.txt", "data/ListaUsuarios.dat");
    printf("\nUsuário removido com sucesso!\n");
    pausar();
}

// Função de listar todos os usuários
void l_usuarios()
{

    struct Usuario u;
    int i = 0;

    FILE *lista_u = fopen("data/ListaUsuarios.dat", "rb");
    if (lista_u == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }
    while (fread(&u, sizeof(struct Usuario), 1, lista_u))
    {
        printf("=====================================================\n");
        printf("USUÁRIO %d\n", i + 1);
        printf("Nome              : %s\n", u.nome);
        printf("Matrícula         : %d\n", u.matricula);
        printf("Curso             : %s\n", u.curso);
        printf("Empréstimos ativos: %d\n", u.quant_emprestimos_ativos);
        i++;
    }
    printf("=====================================================\n");
    printf("Total de usuários: %d\n", i);
    printf("=====================================================\n");
    fclose(lista_u);
    pausar();
    limparBuffer();
    limparTela();
}

// Função de Atualizar dados dos usuários
void a_usuarios()
{

    int matricula_att, pesq;
    int encontrado = 0;
    int cancelar_alteracao = 0;
    struct Usuario u;

    printf("Digite a matrícula do usuário que deseja atualizar: ");
    if (scanf("%d", &matricula_att) != 1)
    {
        printf("\nMatrícula inválida! Digite apenas números.\n");
        limparBuffer();
    }
    limparBuffer();

    FILE *lista_ori = fopen("data/ListaUsuarios.dat", "rb");
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

            if (scanf("%d", &pesq) != 1)
            {
                pesq = -1;
            }

            limparBuffer();

            char temp[50];
            switch (pesq)
            {
            case 0:
                cancelar_alteracao = 1;
                break;

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
                printf("Curso atual: %s\n", u.curso);
                printf("Se quiser manter o atual pressione Enter...\n");
                printf("Se quiser modificar, digite o novo curso: ");
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

    if (cancelar_alteracao)
    {
        printf("\nOperação cancelada pelo usuário.\n");
        remove("data/temp.txt");
        pausar();
        return;
    }

    if (!encontrado)
    {
        printf("Usuário nao encontrado!\n");
        remove("data/temp.txt");
        pausar();
        return;
    }

    remove("data/ListaUsuarios.dat");
    rename("data/temp.txt", "data/ListaUsuarios.dat");
    printf("\nInformações atualizadas com sucesso!\n");
    pausar();
}
