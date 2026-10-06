#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "perguntas.csv"
#define TAM_TEXTO 250
#define TAM_CATEGORIA 50
#define TAM_CURSO 10
#define TAM_RESPOSTA 4

typedef struct {
    int id;
    char texto[TAM_TEXTO];
    char categoria[TAM_CATEGORIA];
    char curso[TAM_CURSO];
    char resposta[TAM_RESPOSTA];
} Pergunta;

void limparBuffer();
void removerQuebraLinha(char *texto);
int textoVazio(const char *texto);
int cursoValido(const char *curso);
int respostaValida(const char *resposta);
void cadastrarPergunta();
void listarPerguntas();
void consultarPorCategoria();
void consultarPorCurso();
void atualizarPergunta();
void excluirPergunta();

int main() {
    int opcao;

    do {
        printf("\n=========================================\n");
        printf(" GERENCIADOR DE PERGUNTAS - QUIZ DE TI\n");
        printf("=========================================\n");
        printf("1 - Cadastrar pergunta\n");
        printf("2 - Listar todas as perguntas\n");
        printf("3 - Consultar perguntas por categoria\n");
        printf("4 - Consultar perguntas por curso\n");
        printf("5 - Atualizar pergunta\n");
        printf("6 - Excluir pergunta\n");
        printf("0 - Sair\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Erro: opcao invalida.\n");
            limparBuffer();
            opcao = -1;
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarPergunta();
                break;
            case 2:
                listarPerguntas();
                break;
            case 3:
                consultarPorCategoria();
                break;
            case 4:
                consultarPorCurso();
                break;
            case 5:
                atualizarPergunta();
                break;
            case 6:
                excluirPergunta();
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Erro: opcao invalida. Escolha uma opcao do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void removerQuebraLinha(char *texto) {
    texto[strcspn(texto, "\n")] = '\0';
}

int textoVazio(const char *texto) {
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ' && texto[i] != '\t' && texto[i] != '\r') {
            return 0;
        }
    }

    return 1;
}

int cursoValido(const char *curso) {
    return strcmp(curso, "CC") == 0 ||
           strcmp(curso, "ES") == 0 ||
           strcmp(curso, "ADS") == 0;
}

int respostaValida(const char *resposta) {
    return strcmp(resposta, "SIM") == 0 ||
           strcmp(resposta, "NAO") == 0;
}

void cadastrarPergunta() {
    FILE *arquivo;
    Pergunta p;
    int resultado;

    printf("\n--- CADASTRAR PERGUNTA ---\n");

    printf("Codigo: ");
    if (scanf("%d", &p.id) != 1 || p.id <= 0) {
        printf("Erro: codigo invalido.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    printf("Pergunta: ");
    fgets(p.texto, TAM_TEXTO, stdin);
    removerQuebraLinha(p.texto);

    if (textoVazio(p.texto)) {
        printf("Erro: a pergunta nao pode estar vazia.\n");
        return;
    }

    printf("Categoria: ");
    fgets(p.categoria, TAM_CATEGORIA, stdin);
    removerQuebraLinha(p.categoria);

    if (textoVazio(p.categoria)) {
        printf("Erro: a categoria nao pode estar vazia.\n");
        return;
    }

    printf("Curso: ");
    fgets(p.curso, TAM_CURSO, stdin);
    removerQuebraLinha(p.curso);

    if (!cursoValido(p.curso)) {
        printf("Erro: curso invalido. Use somente CC, ES ou ADS.\n");
        return;
    }

    printf("Resposta (SIM/NAO): ");
    fgets(p.resposta, TAM_RESPOSTA, stdin);
    removerQuebraLinha(p.resposta);

    if (!respostaValida(p.resposta)) {
        printf("Erro: resposta invalida. Use somente SIM ou NAO.\n");
        return;
    }

    arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para cadastro.\n");
        return;
    }

    resultado = fprintf(arquivo, "%d;%s;%s;%s;%s\n",
                        p.id, p.texto, p.categoria, p.curso, p.resposta);

    fclose(arquivo);

    if (resultado < 0) {
        printf("Erro ao gravar a pergunta.\n");
    } else {
        printf("Pergunta cadastrada com sucesso!\n");
    }
}

void listarPerguntas() {
    FILE *arquivo;
    char linha[400];
    char *campo;
    Pergunta p;
    int encontrou = 0;

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("\nNenhuma pergunta cadastrada ou erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n--- TODAS AS PERGUNTAS ---\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) {
            continue;
        }
        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) {
            continue;
        }
        strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) {
            continue;
        }
        strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) {
            continue;
        }
        strcpy(p.curso, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) {
            continue;
        }
        strcpy(p.resposta, campo);

        printf("\nCodigo: %d\n", p.id);
        printf("Pergunta: %s\n", p.texto);
        printf("Categoria: %s\n", p.categoria);
        printf("Curso: %s\n", p.curso);
        printf("Resposta: %s\n", p.resposta);
        printf("-----------------------------------------\n");

        encontrou = 1;
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma pergunta encontrada.\n");
    }
}

void consultarPorCategoria() {
    FILE *arquivo;
    char linha[400];
    char categoria[TAM_CATEGORIA];
    char *campo;
    Pergunta p;
    int encontrou = 0;

    printf("\n--- CONSULTAR POR CATEGORIA ---\n");
    printf("Categoria desejada: ");
    fgets(categoria, TAM_CATEGORIA, stdin);
    removerQuebraLinha(categoria);

    if (textoVazio(categoria)) {
        printf("Erro: categoria vazia.\n");
        return;
    }

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nPerguntas encontradas:\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.curso, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.resposta, campo);

        if (strcmp(p.categoria, categoria) == 0) {
            printf("[%d] %s - %s - %s\n",
                   p.id, p.texto, p.curso, p.resposta);
            encontrou = 1;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma pergunta encontrada para essa categoria.\n");
    }
}

void consultarPorCurso() {
    FILE *arquivo;
    char linha[400];
    char curso[TAM_CURSO];
    char *campo;
    Pergunta p;
    int encontrou = 0;

    printf("\n--- CONSULTAR POR CURSO ---\n");
    printf("Curso (CC, ES ou ADS): ");
    fgets(curso, TAM_CURSO, stdin);
    removerQuebraLinha(curso);

    if (!cursoValido(curso)) {
        printf("Erro: curso invalido. Use somente CC, ES ou ADS.\n");
        return;
    }

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nPerguntas relacionadas ao curso %s:\n", curso);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.curso, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.resposta, campo);

        if (strcmp(p.curso, curso) == 0) {
            printf("[%d] %s - %s - %s\n",
                   p.id, p.texto, p.categoria, p.resposta);
            encontrou = 1;
        }
    }

    fclose(arquivo);

    if (!encontrou) {
        printf("Nenhuma pergunta encontrada para esse curso.\n");
    }
}

void atualizarPergunta() {
    FILE *arquivo;
    FILE *temporario;
    char linha[400];
    char *campo;
    Pergunta p;
    int id;
    int encontrou = 0;
    int resultado;

    printf("\n--- ATUALIZAR PERGUNTA ---\n");
    printf("Codigo da pergunta: ");

    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Erro: codigo invalido.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    temporario = fopen("perguntas_temp.csv", "w");
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.curso, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.resposta, campo);

        if (p.id == id) {
            encontrou = 1;

            printf("Novo texto: ");
            fgets(p.texto, TAM_TEXTO, stdin);
            removerQuebraLinha(p.texto);
            if (textoVazio(p.texto)) {
                printf("Erro: o texto nao pode estar vazio.\n");
                fclose(arquivo);
                fclose(temporario);
                remove("perguntas_temp.csv");
                return;
            }

            printf("Nova categoria: ");
            fgets(p.categoria, TAM_CATEGORIA, stdin);
            removerQuebraLinha(p.categoria);
            if (textoVazio(p.categoria)) {
                printf("Erro: a categoria nao pode estar vazia.\n");
                fclose(arquivo);
                fclose(temporario);
                remove("perguntas_temp.csv");
                return;
            }

            printf("Novo curso: ");
            fgets(p.curso, TAM_CURSO, stdin);
            removerQuebraLinha(p.curso);
            if (!cursoValido(p.curso)) {
                printf("Erro: curso invalido. Use somente CC, ES ou ADS.\n");
                fclose(arquivo);
                fclose(temporario);
                remove("perguntas_temp.csv");
                return;
            }

            printf("Nova resposta (SIM/NAO): ");
            fgets(p.resposta, TAM_RESPOSTA, stdin);
            removerQuebraLinha(p.resposta);
            if (!respostaValida(p.resposta)) {
                printf("Erro: resposta invalida. Use somente SIM ou NAO.\n");
                fclose(arquivo);
                fclose(temporario);
                remove("perguntas_temp.csv");
                return;
            }
        }

        resultado = fprintf(temporario, "%d;%s;%s;%s;%s\n",
                            p.id, p.texto, p.categoria, p.curso, p.resposta);

        if (resultado < 0) {
            printf("Erro ao gravar o arquivo temporario.\n");
            fclose(arquivo);
            fclose(temporario);
            remove("perguntas_temp.csv");
            return;
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove("perguntas_temp.csv");
        printf("Nenhuma pergunta encontrada com esse codigo.\n");
        return;
    }

    if (remove(ARQUIVO) != 0) {
        printf("Erro ao substituir o arquivo original.\n");
        remove("perguntas_temp.csv");
        return;
    }

    if (rename("perguntas_temp.csv", ARQUIVO) != 0) {
        printf("Erro ao renomear o arquivo temporario.\n");
        return;
    }

    printf("Pergunta atualizada com sucesso!\n");
}

void excluirPergunta() {
    FILE *arquivo;
    FILE *temporario;
    char linha[400];
    char *campo;
    Pergunta p;
    int id;
    int encontrou = 0;
    int resultado;

    printf("\n--- EXCLUIR PERGUNTA ---\n");
    printf("Codigo da pergunta: ");

    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Erro: codigo invalido.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    temporario = fopen("perguntas_temp.csv", "w");
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        campo = strtok(linha, ";");
        if (campo == NULL) continue;
        p.id = atoi(campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.texto, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.categoria, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.curso, campo);

        campo = strtok(NULL, ";");
        if (campo == NULL) continue;
        strcpy(p.resposta, campo);

        if (p.id == id) {
            encontrou = 1;
            continue;
        }

        resultado = fprintf(temporario, "%d;%s;%s;%s;%s\n",
                            p.id, p.texto, p.categoria, p.curso, p.resposta);

        if (resultado < 0) {
            printf("Erro ao gravar o arquivo temporario.\n");
            fclose(arquivo);
            fclose(temporario);
            remove("perguntas_temp.csv");
            return;
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove("perguntas_temp.csv");
        printf("Nenhuma pergunta encontrada com esse codigo.\n");
        return;
    }

    if (remove(ARQUIVO) != 0) {
        printf("Erro ao substituir o arquivo original.\n");
        remove("perguntas_temp.csv");
        return;
    }

    if (rename("perguntas_temp.csv", ARQUIVO) != 0) {
        printf("Erro ao renomear o arquivo temporario.\n");
        return;
    }

    printf("Pergunta excluida com sucesso!\n");
}
