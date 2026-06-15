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
│   ├── biblioteca.txt          # Arte ASCII exibida no menu principal
│   ├── devolucoes.txt          # Arte ASCII exibida no menu de devoluções
│   ├── emprestimos.txt         # Arte ASCII exibida no menu de empréstimos
│   ├── livros.txt              # Arte ASCII exibida no menu de livros
│   ├── relatorios.txt          # Arte ASCII exibida no menu de relatórios
│   └── usuarios.txt            # Arte ASCII exibida no menu de usuários
│
├── build/                      # Arquivos gerados pelo Makefile
│
├── data/
│   ├── listaLivros.bin         # Armazenamento dos livros
│   ├── listaUsuarios.bin       # Armazenamento dos usuários
│   └── listaEmprestimos.bin    # Armazenamento dos empréstimos
│
├── docs/
│   ├── Trabalho_PA_2026_1.pdf  # Especificações solicitadas para o projeto
│   └── Relatorio_PA_2026_1.pdf # Relatório do projeto
│
├── include/
│   ├── auxiliares.h            # Funções auxiliares
│   ├── emprestimos.h           # Operações de empréstimos
│   ├── livros.h                # Operações de livros
│   ├── menu.h                  # Menus do sistema
│   ├── relatorios.h            # Relatórios
│   └── usuarios.h              # Operações de usuários
│
├── src/
│   ├── auxiliares.c
│   ├── emprestimos.c
│   ├── livros.c
│   ├── main.c
│   ├── menu.c
│   ├── relatorios.c
│   └── usuarios.c
│
├── .gitignore                  # Arquivos ignorados pelo Git
├── Makefile                    # Automação da compilação
└── README.md                   # Documentação do projeto
```

---

## Observações

* Os arquivos de dados são armazenados na pasta `data/`.
* Os recursos visuais do sistema estão na pasta `assets/`.
* O projeto utiliza compilação modular e Makefile para automatizar a construção do executável.
* Desenvolvido e testado com GCC 15.2.0 (MSYS2 UCRT64).
* O projeto foi desenvolvido utilizando o locale `pt_BR.UTF-8`.
* Recomenda-se utilizar arquivos-fonte salvos em UTF-8 e executar o sistema em um terminal compatível com UTF-8.