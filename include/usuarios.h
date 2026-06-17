#ifndef USUARIOS_H_
#define USUARIOS_H_

// Estrutura de um Usuário (atributos)
struct Usuario
{
    int matricula;
    char nome[50];
    char curso[50];
    int quant_emprestimos_ativos;
};

// Função para cadastrar usuários
void c_usuarios();

// Função para pesquisar usuários
void p_usuarios();

// Função para remover usuários
void r_usuarios();

// Função de listar todos os usuários
void l_usuarios();

// Função de Atualizar dados dos usuários
void a_usuarios();

#endif