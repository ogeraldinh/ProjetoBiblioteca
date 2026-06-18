# Sistema de Gerenciamento de Biblioteca

Projeto desenvolvido para a disciplina de **Programação e Algoritmos** utilizando a linguagem **C**.

O sistema permite o gerenciamento de um acervo de livros, usuários e empréstimos, com persistência dos dados em arquivos e capacidade de gerar relatórios em arquivos de texto.

---

## Autores

* [Geraldo Duarte de Medeiros Neto](https://github.com/ogeraldinh)
- [João Batista Alves de Sousa Júnior](https://github.com/JB-2612)

---

## Funcionalidades

* Cadastro de usuários
* Consulta de usuários
* Cadastro de livros
* Consulta de livros
* Controle de empréstimos
* Persistência de dados em arquivos binários
* Interface em terminal

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

## Compilação

### Windows

```bash
mingw32-make
```

### Linux

```bash
make
```

Após a compilação será gerado o executável:

```text
biblioteca.exe
```

---

## Execução

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
│   ├── relatorios_especificos/  # Diretório de criação dos relatórios específicos
│   └── relatorios_genericos/    # Diretório de criação dos relatórios genéricos
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