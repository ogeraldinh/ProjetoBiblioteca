// Bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Módulos Locais
#include "../include/auxiliares.h"


// Função para exibição de títulos nos menus
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

// Função de limpar o buffer
void limparBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// Função que pausa a execução do programa
void pausar()
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// Função que limpa as informações da tela
void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função de exibição de erro ao receber entradas inválidas
void erroEntrada(const char *mensagem)
{
    printf("\n%s\n", mensagem);

    limparBuffer();
    pausar();
    limparTela();
}

// Função para confirmações necessárias
int confirmar(const char *mensagem)
{
    char resposta;

    printf("%s (S/N): ", mensagem);
    scanf(" %c", &resposta);

    return resposta == 'S' || resposta == 's';
}

// Função para obter a data atual do sistema
void obterDataAtual(char *data)
{
    time_t agora = time(NULL);

    struct tm *tm_info = localtime(&agora);

    strftime(data, 11, "%d/%m/%Y", tm_info);
}

// Função para obter a data prevista das devoluções
void obterDataFutura(char *data, int dias)
{
    time_t agora = time(NULL);

    agora += dias * 24 * 60 * 60;

    struct tm *tm_info = localtime(&agora);

    strftime(data, 11, "%d/%m/%Y", tm_info);
}

// Função que converte as datas para valores manipuláveis
int converterDataParaDias(const char *data)
{
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    return dia + (mes - 1) * 30 + ano * 365;
}
