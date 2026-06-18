# Sistema de Gerenciamento de Biblioteca

![C](https://img.shields.io/badge/Language-C-blue.svg)
![GCC](https://img.shields.io/badge/Compiler-GCC%2015.2.0-orange.svg)
![Makefile](https://img.shields.io/badge/Build-Makefile-green.svg)

Projeto desenvolvido como projeto final para a disciplina de **Programação e Algoritmos**.

O Sistema de Gerenciamento de Biblioteca é uma aplicação de terminal desenvolvida em linguagem **C** para realizar o controle de livros, usuários, empréstimos e devoluções de uma biblioteca.

Os dados são armazenados de forma persistente em arquivos binários (.dat), permitindo que as informações sejam preservadas entre execuções do programa. Além disso, o sistema é capaz de gerar relatórios em arquivos texto (.txt) legíveis, facilitando consultas e análises do acervo e das movimentações realizadas.

---

## Autores

* [Geraldo Duarte de Medeiros Neto](https://github.com/ogeraldinh)
* [João Batista Alves de Sousa Júnior](https://github.com/JB-2612)

---

## Funcionalidades

### Usuários
* Cadastro de usuários
* Consulta de usuários
* Atualização de dados usuários
* Remoção de usuários

### Livros
* Cadastro de livros
* Consulta de livros
* Atualização de livros
* Consulta de usuários que possuem determinado livro
* Remoção de livros

### Empréstimos
* Registro de empréstimos
* Registro de devoluções
* Consulta de empréstimos ativos por usuário
* Consulta de usuários que possuem determinado livro

### Persistência
* Armazenamento permanente em arquivos binários (.dat)
* Geração de relatórios em arquivos texto (.txt)

### Relatórios
* Livros mais emprestados
* Empréstimos em atraso
* Acervo disponível
* Histórico de empréstimos por usuário

### Interface
* Menus interativos em terminal
* Validação de entradas do usuário
* Arte ASCII nos módulos do sistema

---

## Persistência de Dados

Os dados do sistema são armazenados em arquivos binários localizados na pasta `data/`.

| Arquivo | Conteúdo |
|----------|-----------|
| listaUsuarios.dat | Registros de usuários |
| listaLivros.dat | Registros de livros |
| listaEmprestimos.dat | Registros de empréstimos |

---

## Relatórios Gerados

O sistema pode gerar automaticamente os seguintes relatórios:

| Relatório | Descrição |
|------------|------------|
| RelatorioMaisEmprestado.txt | Lista os livros ordenados pela quantidade de empréstimos |
| RelatorioAtrasos.txt | Exibe empréstimos com devolução em atraso |
| RelatorioAcervoDisponivel.txt | Lista os livros atualmente disponíveis |
| HistoricoRelatorio.txt | Histórico completo de empréstimos de um usuário |

---

## Requisitos

### Windows (MSYS2)

Verifique se os programas estão instalados:

```bash
gcc --version
mingw32-make --version
```

### Linux

```bash
gcc --version
make --version
```

---

## Instalação

No terminal, digite:

```bash
git clone https://github.com/ogeraldinh/ProjetoBiblioteca
```

Após isso, entre no diretório do projeto.

---

## Compilação

Para a compilação do sistema, digite no terminal:

### Windows

```bash
mingw32-make
```

### Linux

```bash
make
```

Após a compilação será gerado o executável:

### Windows

```text
biblioteca.exe
```

### Linux

```text
biblioteca
```

---

## Execução

Para a execução do sistema, digite no terminal:

### Windows

```bash
.\biblioteca.exe
```

ou

```bash
mingw32-make run
```

### Linux

```bash
./biblioteca
```

ou

```bash
make run
```

---

## Depuração

Para depuração, utilize:

### Windows

```bash
mingw32-make debug
```

ou

```bash
gdb biblioteca.exe
```

### Linux

```bash
make debug
```

ou

```bash
gdb biblioteca
```

---

## Limpeza dos Arquivos Gerados

Caso queira remover os arquivos de compilação gerados:

### Windows

```bash
mingw32-make clean
```

### Linux

```bash
make clean
```

---

## Estrutura do Projeto

```text
ProjetoBiblioteca/
│
├── assets/
│   ├── biblioteca.txt          # Arte ASCII exibida no menu principal do sistema
│   ├── devolucoes.txt          # Arte ASCII utilizada no módulo de devoluções
│   ├── emprestimos.txt         # Arte ASCII utilizada no módulo de empréstimos
│   ├── livros.txt              # Arte ASCII utilizada no módulo de gerenciamento de livros
│   ├── relatorios.txt          # Arte ASCII utilizada no módulo de relatórios
│   └── usuarios.txt            # Arte ASCII utilizada no módulo de gerenciamento de usuários
│
├── build/                      # Arquivos objeto e executáveis gerados durante a compilação
│
├── data/
│   ├── listaLivros.dat         # Arquivo binário contendo os registros de livros
│   ├── listaUsuarios.dat       # Arquivo binário contendo os registros de usuários
│   └── listaEmprestimos.dat    # Arquivo binário contendo os registros de empréstimos
│
├── docs/
│   ├── Trabalho_PA_2026_1.pdf  # Enunciado e requisitos do trabalho
│   └── Relatorio_PA_2026_1.pdf # Relatório técnico do projeto
│
├── include/
│   ├── auxiliares.h            # Protótipos de funções auxiliares e utilitárias
│   ├── emprestimos.h           # Protótipos das operações de empréstimos e devoluções
│   ├── livros.h                # Protótipos das operações de gerenciamento de livros
│   ├── menu.h                  # Protótipos dos menus e navegação do sistema
│   ├── relatorios.h            # Protótipos das funções de geração de relatórios
│   └── usuarios.h              # Protótipos das operações de gerenciamento de usuários
│
├── relatorios/
│   ├── relatorios_especificos/ # Diretório de criação dos relatórios específicos
│   └── relatorios_genericos/   # Diretório de criação dos relatórios genéricos
│
├── src/
│   ├── auxiliares.c            # Implementação das funções auxiliares
│   ├── emprestimos.c           # Implementação das operações de empréstimos e devoluções
│   ├── livros.c                # Implementação das operações relacionadas aos livros
│   ├── main.c                  # Ponto de entrada do programa
│   ├── menu.c                  # Implementação dos menus do sistema
│   ├── relatorios.c            # Implementação dos relatórios do sistema
│   └── usuarios.c              # Implementação das operações relacionadas aos usuários
│
├── .gitignore                  # Arquivos e diretórios ignorados pelo Git
├── Makefile                    # Automatiza o processo de compilação do projeto
└── README.md                   # Documentação geral do projeto
```

---

## Observações

* Os arquivos de dados são armazenados na pasta `data/`.
* Os recursos visuais do sistema estão na pasta `assets/`.
* O projeto utiliza compilação modular e Makefile para automatizar a construção do executável.
* Desenvolvido e testado com GCC 15.2.0 (MSYS2 UCRT64).
* O projeto foi desenvolvido utilizando o locale `pt_BR.UTF-8`.
* Recomenda-se utilizar arquivos-fonte salvos em UTF-8 e executar o sistema em um terminal compatível com UTF-8.
