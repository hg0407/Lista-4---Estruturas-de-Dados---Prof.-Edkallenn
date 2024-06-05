/*
** Função : Gerir os livros de uma biblioteca usando lista encadeada
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: Implementa inserção ordenada, remoção, alteração, busca por nome do livro e busca por nome do autor
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Livro {
    char autor[MAX];
    char titulo[MAX];
    char editora[MAX];
    int ano;
    struct Livro *prox;
} Livro;

Livro* criarLivro(char *autor, char *titulo, char *editora, int ano) {
    Livro *novoLivro = (Livro*) malloc(sizeof(Livro));
    strcpy(novoLivro->autor, autor);
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->editora, editora);
    novoLivro->ano = ano;
    novoLivro->prox = NULL;
    return novoLivro;
}

void inserirLivro(Livro **lista, Livro *novoLivro) {
    Livro *atual;
    if (*lista == NULL || strcmp((*lista)->titulo, novoLivro->titulo) > 0) {
        novoLivro->prox = *lista;
        *lista = novoLivro;
    } else {
        atual = *lista;
        while (atual->prox != NULL && strcmp(atual->prox->titulo, novoLivro->titulo) < 0) {
            atual = atual->prox;
        }
        novoLivro->prox = atual->prox;
        atual->prox = novoLivro;
    }
}

void removerLivro(Livro **lista, char *titulo) {
    Livro *atual = *lista;
    Livro *anterior = NULL;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Livro não encontrado.\n");
        return;
    }
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    printf("Livro removido com sucesso.\n");
}

void alterarLivro(Livro *lista, char *titulo, char *novoAutor, char *novoTitulo, char *novaEditora, int novoAno) {
    Livro *atual = lista;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Livro não encontrado.\n");
        return;
    }
    strcpy(atual->autor, novoAutor);
    strcpy(atual->titulo, novoTitulo);
    strcpy(atual->editora, novaEditora);
    atual->ano = novoAno;
    printf("Livro alterado com sucesso.\n");
}

void buscarLivroPorTitulo(Livro *lista, char *titulo) {
    Livro *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Autor: %s\n", atual->autor);
            printf("Título: %s\n", atual->titulo);
            printf("Editora: %s\n", atual->editora);
            printf("Ano: %d\n", atual->ano);
            return;
        }
        atual = atual->prox;
    }
    printf("Livro não encontrado.\n");
}

void buscarLivroPorAutor(Livro *lista, char *autor) {
    Livro *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->autor, autor) == 0) {
            printf("Autor: %s\n", atual->autor);
            printf("Título: %s\n", atual->titulo);
            printf("Editora: %s\n", atual->editora);
            printf("Ano: %d\n", atual->ano);
        }
        atual = atual->prox;
    }
}

void exibirLivros(Livro *lista) {
    Livro *atual = lista;
    while (atual != NULL) {
        printf("Autor: %s\n", atual->autor);
        printf("Título: %s\n", atual->titulo);
        printf("Editora: %s\n", atual->editora);
        printf("Ano: %d\n", atual->ano);
        printf("\n");
        atual = atual->prox;
    }
}

int main() {
    Livro *lista = NULL;
    int escolha, ano;
    char autor[MAX], titulo[MAX], editora[MAX];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir livro\n");
        printf("2. Remover livro\n");
        printf("3. Alterar livro\n");
        printf("4. Buscar livro por título\n");
        printf("5. Buscar livro por autor\n");
        printf("6. Exibir todos os livros\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Para capturar o caractere '\n' deixado pelo scanf

        switch (escolha) {
            case 1:
                printf("Digite o autor: ");
                fgets(autor, MAX, stdin);
                autor[strcspn(autor, "\n")] = '\0';
                printf("Digite o título: ");
                fgets(titulo, MAX, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Digite a editora: ");
                fgets(editora, MAX, stdin);
                editora[strcspn(editora, "\n")] = '\0';
                printf("Digite o ano de edição: ");
                scanf("%d", &ano);
                getchar();
                inserirLivro(&lista, criarLivro(autor, titulo, editora, ano));
                break;
            case 2:
                printf("Digite o título do livro a ser removido: ");
                fgets(titulo, MAX, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                removerLivro(&lista, titulo);
                break;
            case 3:
                printf("Digite o título do livro a ser alterado: ");
                fgets(titulo, MAX, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Digite o novo autor: ");
                fgets(autor, MAX, stdin);
                autor[strcspn(autor, "\n")] = '\0';
                printf("Digite o novo título: ");
                fgets(titulo, MAX, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Digite a nova editora: ");
                fgets(editora, MAX, stdin);
                editora[strcspn(editora, "\n")] = '\0';
                printf("Digite o novo ano de edição: ");
                scanf("%d", &ano);
                getchar();
                alterarLivro(lista, titulo, autor, titulo, editora, ano);
                break;
            case 4:
                printf("Digite o título do livro a ser buscado: ");
                fgets(titulo, MAX, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                buscarLivroPorTitulo(lista, titulo);
                break;
            case 5:
                printf("Digite o autor do livro a ser buscado: ");
                fgets(autor, MAX, stdin);
                autor[strcspn(autor, "\n")] = '\0';
                buscarLivroPorAutor(lista, autor);
                break;
            case 6:
                exibirLivros(lista);
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
