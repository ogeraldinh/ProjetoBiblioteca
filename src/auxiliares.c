#include "../include/auxiliares.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void exibirTitulo(const char *arquivo)
{
    FILE *title;
    char linha[50];

    title = fopen(arquivo, "r");

    if (title == NULL)
    {
        printf("Erro ao abrir %s\n", arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), title))
    {
        printf("%s", linha);
    }

    fclose(title);
}
void limparBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar()
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void erroEntrada(const char *mensagem)
{
    printf("\n%s\n", mensagem);

    limparBuffer();
    pausar();
    limparTela();
}

void lerString(char *texto, int tamanho)
{
    fgets(texto, tamanho, stdin);

    texto[strcspn(texto, "\n")] = '\0';
}

int confirmar(const char *mensagem)
{
    char resposta;

    printf("%s (S/N): ", mensagem);
    scanf(" %c", &resposta);

    return resposta == 'S' || resposta == 's';
}

void obterDataAtual(char *data)
{
    time_t agora = time(NULL);

    struct tm *tm_info = localtime(&agora);

    strftime(data, 11, "%d/%m/%Y", tm_info);
}