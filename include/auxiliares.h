#ifndef AUXILIARES_H
#define AUXILIARES_H

// Função para exibição de títulos nos menus
void exibirTitulo(const char *arquivo);

// Função de limpar o buffer
void limparBuffer();

// Função que pausa a execução do programa
void pausar();

// Função que limpa as informações da tela
void limparTela();

// Função de exibição de erro ao receber entradas inválidas
void erroEntrada(const char *mensagem);

// Função para confirmações necessárias
int confirmar(const char *mensagem);

// Função para obter a data atual do sistema
void obterDataAtual(char *data);

// Função para obter a data prevista das devoluções
void obterDataFutura(char *data, int dias);

// Função que converte as datas para valores manipuláveis
int converterDataParaDias(const char *data);

#endif