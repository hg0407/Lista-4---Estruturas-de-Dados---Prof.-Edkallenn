/*
** Função : Gerenciar uma pilha de processos
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: O programa permite incluir, retirar e encerrar processos em uma pilha, exibindo o estado atual da pilha
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRICAO 100

typedef struct Processo {
    int id;
    char descricao[MAX_DESCRICAO];
    struct Processo *prox;
} Processo;

typedef struct {
    Processo *topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
}

int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}

void push(Pilha *p, int id, char *descricao) {
    Processo *novo = (Processo *)malloc(sizeof(Processo));
    novo->id = id;
    strcpy(novo->descricao, descricao);
    novo->prox = p->topo;
    p->topo = novo;
    printf("Processo #%d - %s incluído na pilha.\n", id, descricao);
}

void pop(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia.\n");
        return;
    }
    Processo *removido = p->topo;
    p->topo = p->topo->prox;
    printf("Removido o processo #%d - %s da pilha.\n", removido->id, removido->descricao);
    free(removido);
}

void exibirPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia.\n");
        return;
    }
    Processo *atual = p->topo;
    printf("Conteúdo da pilha:\n");
    while (atual != NULL) {
        printf("Processo #%d - %s\n", atual->id, atual->descricao);
        atual = atual->prox;
    }
}

void esvaziarPilha(Pilha *p) {
    while (!pilhaVazia(p)) {
        pop(p);
    }
}

int main() {
    Pilha pilha;
    inicializarPilha(&pilha);

    int escolha, id;
    char descricao[MAX_DESCRICAO];

    do {
        printf("\nMenu:\n");
        printf("1. Incluir processo\n");
        printf("2. Retirar processo\n");
        printf("3. Exibir pilha\n");
        printf("0. Encerrar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o identificador do processo: ");
                scanf("%d", &id);
                printf("Digite a descrição do processo: ");
                getchar(); // Para capturar o caractere '\n' deixado pelo scanf
                fgets(descricao, MAX_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = '\0';
                push(&pilha, id, descricao);
                exibirPilha(&pilha);
                break;
            case 2:
                pop(&pilha);
                exibirPilha(&pilha);
                break;
            case 3:
                exibirPilha(&pilha);
                break;
            case 0:
                esvaziarPilha(&pilha);
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    return 0;
}

   
