/*
** Função : Implementar uma pilha de números reais
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: O programa permite inserir (push), retirar (pop) elementos na pilha, exibir a pilha e verificar se está vazia
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    float elementos[MAX_SIZE];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, float valor) {
    if (p->topo == MAX_SIZE - 1) {
        printf("Erro: Pilha cheia\n");
        return;
    }
    p->topo++;
    p->elementos[p->topo] = valor;
}

float pop(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
    float valor = p->elementos[p->topo];
    p->topo--;
    return valor;
}
void exibirPilha(Pilha *p) {
    printf("Pilha:");
    for (int i = 0; i <= p->topo; i++) {
        printf(" %.2f", p->elementos[i]);
    }
    printf("\n");
}

int main() {
    Pilha pilha;
    inicializarPilha(&pilha);

    int escolha;
    float valor;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir (push)\n");
        printf("2. Retirar (pop)\n");
        printf("3. Exibir pilha\n");
        printf("4. Verificar se a pilha está vazia\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%f", &valor);
                push(&pilha, valor);
                exibirPilha(&pilha);
                break;
            case 2:
                if (!pilhaVazia(&pilha)) {
                    valor = pop(&pilha);
                    printf("Valor retirado: %.2f\n", valor);
                    exibirPilha(&pilha);
                } else {
                    printf("A pilha está vazia.\n");
                }
                break;
            case 3:
                exibirPilha(&pilha);
                break;
            case 4:
                if (pilhaVazia(&pilha)) {
                    printf("A pilha está vazia.\n");
                } else {
                    printf("A pilha não está vazia.\n");
                }
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    return 0;
}
