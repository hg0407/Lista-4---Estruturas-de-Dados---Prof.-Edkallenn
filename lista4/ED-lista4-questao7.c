/*
** Função : Sistema de gerenciamento de atendimento para uma clínica médica usando fila
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: Implementa adição de paciente, retorno e remoção do próximo paciente, e quantidade de pacientes na fila
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

typedef struct Paciente {
    char nome[MAX_NOME];
    struct Paciente *prox;
} Paciente;

typedef struct {
    Paciente *frente;
    Paciente *tras;
    int quantidade;
} FilaAtendimento;

void inicializarFila(FilaAtendimento *fila) {
    fila->frente = NULL;
    fila->tras = NULL;
    fila->quantidade = 0;
}

void adicionarPaciente(FilaAtendimento *fila, char *nome) {
    Paciente *novo = (Paciente *)malloc(sizeof(Paciente));
    strcpy(novo->nome, nome);
    novo->prox = NULL;
    if (fila->tras == NULL) {
        fila->frente = novo;
    } else {
        fila->tras->prox = novo;
    }
    fila->tras = novo;
    fila->quantidade++;
}

char* proximoPaciente(FilaAtendimento *fila) {
    if (fila->frente == NULL) {
        return "Não há pacientes na fila.";
    }
    Paciente *temp = fila->frente;
    char *nome = (char *)malloc(MAX_NOME * sizeof(char));
    strcpy(nome, temp->nome);
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    fila->quantidade--;
    free(temp);
    return nome;
}

void exibirFila(FilaAtendimento *fila) {
    if (fila->frente == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    Paciente *atual = fila->frente;
    while (atual != NULL) {
        printf("Paciente: %s\n", atual->nome);
        atual = atual->prox;
    }
    printf("Quantidade de pacientes na fila: %d\n", fila->quantidade);
}

int main() {
    FilaAtendimento fila;
    inicializarFila(&fila);

    int escolha;
    char nome[MAX_NOME];

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar paciente\n");
        printf("2. Retornar próximo paciente\n");
        printf("3. Exibir fila\n");
        printf("0. Encerrar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Para capturar o caractere '\n' deixado pelo scanf

        switch (escolha) {
            case 1:
                printf("Digite o nome do paciente: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                adicionarPaciente(&fila, nome);
                break;
            case 2: {
                char *proximo = proximoPaciente(&fila);
                printf("Próximo paciente: %s\n", proximo);
                free(proximo);
                break;
            }
            case 3:
                exibirFila(&fila);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    // Liberar memória alocada
    while (fila.frente != NULL) {
        Paciente *temp = fila.frente;
        fila.frente = fila.frente->prox;
        free(temp);
    }

    return 0;
}
