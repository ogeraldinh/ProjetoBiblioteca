#ifndef AUXILIARES_H
#define AUXILIARES_H

void exibirTitulo(const char *arquivo);

void limparBuffer();

void pausar();

void limparTela();

void erroEntrada(const char *mensagem);

void lerString(char *texto, int tamanho);

int confirmar(const char *mensagem);

void obterDataAtual(char *data);

void obterDataFutura(char *data, int dias);

int converterDataParaDias(const char *data);

#endif