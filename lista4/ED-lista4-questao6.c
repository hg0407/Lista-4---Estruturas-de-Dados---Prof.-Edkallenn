/*
** Função : Simular uma lista de compras usando lista encadeada
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: O programa permite inserir, remover, consultar e mostrar todos os itens da lista de compras
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_PRODUTO 100

typedef struct Item {
    char nome[MAX_NOME_PRODUTO];
    int quantidade;
    struct Item *prox;
} Item;

Item* criarItem(char *nome, int quantidade) {
    Item *novoItem = (Item *)malloc(sizeof(Item));
    strcpy(novoItem->nome, nome);
    novoItem->quantidade = quantidade;
    novoItem->prox = NULL;
    return novoItem;
}

void inserirItem(Item **lista, char *nome, int quantidade) {
    Item *novoItem = criarItem(nome, quantidade);
    novoItem->prox = *lista;
    *lista = novoItem;
}

void removerItem(Item **lista, char *nome) {
    Item *atual = *lista;
    Item *anterior = NULL;
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Item não encontrado.\n");
        return;
    }
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    printf("Item removido com sucesso.\n");
}

void consultarItem(Item *lista, char *nome) {
    Item *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Produto: %s, Quantidade: %d\n", atual->nome, atual->quantidade);
            return;
        }
        atual = atual->prox;
    }
    printf("Item não encontrado.\n");
}

void exibirLista(Item *lista) {
    Item *atual = lista;
    while (atual != NULL) {
        printf("Produto: %s, Quantidade: %d\n", atual->nome, atual->quantidade);
        atual = atual->prox;
    }
}

int main() {
    Item *lista = NULL;
    int escolha, quantidade;
    char nome[MAX_NOME_PRODUTO];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Consultar item\n");
        printf("4. Mostrar todos os itens\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Para capturar o caractere '\n' deixado pelo scanf

        switch (escolha) {
            case 1:
                printf("Digite o nome do produto: ");
                fgets(nome, MAX_NOME_PRODUTO, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                getchar();
                inserirItem(&lista, nome, quantidade);
                break;
            case 2:
                printf("Digite o nome do produto a ser removido: ");
                fgets(nome, MAX_NOME_PRODUTO, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerItem(&lista, nome);
                break;
            case 3:
                printf("Digite o nome do produto a ser consultado: ");
                fgets(nome, MAX_NOME_PRODUTO, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                consultarItem(lista, nome);
                break;
            case 4:
                exibirLista(lista);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    // Liberar memória alocada
    while (lista != NULL) {
        Item *temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}
