/*
** Função : Classificar os elementos de um vetor em ordem crescente usando o algoritmo de seleção
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: Implementa o algoritmo de seleção para ordenar um vetor de números gerados aleatoriamente
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void classificacaoPorSelecao(int *vetor, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        trocar(&vetor[min_idx], &vetor[i]);
    }
}

void exibirVetor(int *vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Digite o número de elementos do vetor: ");
    scanf("%d", &n);

    int *vetor = (int *)malloc(n * sizeof(int));

    srand(time(0));
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 100;
    }

    printf("Vetor gerado aleatoriamente:\n");
    exibirVetor(vetor, n);

    classificacaoPorSelecao(vetor, n);

    printf("Vetor ordenado:\n");
    exibirVetor(vetor, n);

    free(vetor);

    return 0;
}
