# 📚 Sistema de Gerenciamento de Perguntas para Quiz de Cursos de TI

Projeto prático em **linguagem C** para cadastrar e organizar as perguntas de um futuro quiz de orientação voltado a estudantes do Ensino Médio que desejam conhecer os cursos de **Ciência da Computação (CC)**, **Engenharia de Software (ES)** e **Análise e Desenvolvimento de Sistemas (ADS)**.

> **Escopo desta etapa:** o sistema cuida apenas do **banco de perguntas**. A aplicação do quiz, o cálculo de pontuação e a indicação de curso ficam para uma etapa futura.

---

## 👥 Identificação

- **Turma:** _preencher_
- **Integrantes:**
  1. Nayra Costa
  2. Dennis Oliveira
  3. João Henrique
  4. Murilo Morata
  5. Felipe Gustavo
  6. Andrey Heneique
  7. Matheus Lopes
- **Vídeo de apresentação:** _colar aqui o link do YouTube_

---

## 🎯 Descrição do sistema

O programa funciona pelo terminal, com um menu de opções, e permite gerenciar as perguntas do quiz. Todas as perguntas ficam salvas no arquivo `perguntas.csv`, então os dados continuam disponíveis depois que o programa é encerrado.

Cada pergunta possui:

| Campo | Descrição |
|---|---|
| `id` | Código identificador da pergunta |
| `texto` | Texto da pergunta |
| `categoria` | Categoria da pergunta (ex.: Raciocinio, Projetos, Aprendizagem) |
| `curso` | Curso relacionado: `CC`, `ES` ou `ADS` |
| `resposta` | Resposta esperada: `SIM` ou `NAO` |

---

## ✨ Funcionalidades

```
=========================================
GERENCIADOR DE PERGUNTAS - QUIZ DE TI
=========================================
1 - Cadastrar pergunta
2 - Listar todas as perguntas
3 - Consultar perguntas por categoria
4 - Consultar perguntas por curso
5 - Atualizar pergunta
6 - Excluir pergunta
0 - Sair
-----------------------------------------
```

- **Cadastrar pergunta:** grava uma nova pergunta no CSV sem apagar as existentes.
- **Listar todas:** lê o arquivo e exibe código, texto, categoria, curso e resposta.
- **Consultar por categoria:** mostra todas as perguntas da categoria informada.
- **Consultar por curso:** mostra somente as perguntas de `CC`, `ES` ou `ADS`.
- **Atualizar pergunta:** localiza pela código e permite alterar texto, categoria, curso e resposta.
- **Excluir pergunta:** remove a pergunta escolhida sem apagar as demais.

---

## ✅ Validações

- Opção do menu válida
- Código da pergunta válido
- Curso aceito somente como `CC`, `ES` ou `ADS`
- Resposta aceita somente como `SIM` ou `NAO`
- Perguntas vazias não são gravadas
- Dados inválidos nunca são gravados no CSV
- Mensagem clara quando nenhuma pergunta é encontrada
- Tratamento de erro na abertura do arquivo

---

## 🗂️ Formato do arquivo `perguntas.csv`

Uma pergunta por linha, com campos separados por ponto e vírgula (`;`):

```
1;Voce gosta de resolver problemas de logica?;Raciocinio;CC;SIM
2;Voce se interessa por planejar sistemas grandes?;Projetos;ES;SIM
3;Voce prefere aprender criando aplicacoes praticas?;Aprendizagem;ADS;SIM
4;Voce prefere atividades com pouca programacao?;Interesse;CC;NAO
```

---

## 🧱 Estrutura de dados

```c
typedef struct {
    int id;
    char texto[250];
    char categoria[50];
    char curso[10];
    char resposta[4];
} Pergunta;
```

---

## 🛠️ Conteúdos de C utilizados

`struct` · funções · menu com `switch` · arquivos CSV · `fopen()` e `fclose()` · `fprintf()` e `fgets()` · `strtok()` · `strcpy()` e `strcmp()` · estruturas de repetição e condicionais

---

## ▶️ Como compilar e executar

Pré-requisito: compilador **GCC** instalado.

```bash
gcc main.c -o quiz
./quiz
```

No Windows:

```bash
gcc main.c -o quiz.exe
quiz.exe
```

> Mantenha o arquivo `perguntas.csv` na mesma pasta do executável. Se ele ainda não existir, o programa o cria ao cadastrar a primeira pergunta.

---

## 📁 Estrutura do repositório

```
├── main.c            # código-fonte completo
├── perguntas.csv     # arquivo usado nos testes
└── README.md         # documentação do projeto
```

---

## 🧪 Exemplo de uso

```
Codigo: 10
Pergunta: Voce gosta de entender como os computadores funcionam?
Categoria: Interesse
Curso: CC
Resposta (SIM/NAO): SIM
Pergunta cadastrada com sucesso!
```

---

## 🎬 Apresentação

O vídeo de apresentação (máximo de 10 minutos) demonstra cadastro, listagem, consultas por categoria e por curso, atualização, exclusão, validações e o conteúdo do `perguntas.csv`.

🔗 _colar aqui o link do vídeo_
