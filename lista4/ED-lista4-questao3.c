/*
** Função : Calcular e exibir informações de perfil de saúde
** Autor : Hygor Alves
** Data : 03/06/2024
** Observações: O programa calcula e exibe a idade, IMC, frequência cardíaca máxima e ideal, e expectativa de vida
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 80

typedef struct {
    int dia;
    int mes;
    int ano;
} DataNascimento;

typedef struct {
    char nome[MAX_NOME];
    char sexo;
    DataNascimento dataNascimento;
    float altura;
    float peso;
} PerfilSaude;

void calcularIdade(PerfilSaude *perfil, int *idade) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *idade = tm.tm_year + 1900 - perfil->dataNascimento.ano;
    if (tm.tm_mon + 1 < perfil->dataNascimento.mes || 
        (tm.tm_mon + 1 == perfil->dataNascimento.mes && tm.tm_mday < perfil->dataNascimento.dia)) {
        (*idade)--;
    }
}

void calcularFrequenciaCardiaca(PerfilSaude *perfil, int idade, float *freqMax, float *freqIdeal) {
    if (perfil->sexo == 'M' || perfil->sexo == 'm') {
        *freqMax = 220 - idade;
    } else if (perfil->sexo == 'F' || perfil->sexo == 'f') {
        *freqMax = 226 - idade;
    } else {
        *freqMax = 0;
        *freqIdeal = 0;
        return;
    }
    *freqIdeal = 0.7 * (*freqMax);
}

float calcularIMC(PerfilSaude *perfil) {
    return perfil->peso / (perfil->altura * perfil->altura);
}

void exibirPerfil(PerfilSaude *perfil) {
    printf("Nome: %s\n", perfil->nome);
    printf("Sexo: %c\n", perfil->sexo);
    printf("Data de Nascimento: %02d/%02d/%04d\n", perfil->dataNascimento.dia, perfil->dataNascimento.mes, perfil->dataNascimento.ano);
    printf("Altura: %.2f m\n", perfil->altura);
    printf("Peso: %.2f kg\n", perfil->peso);
}

int main() {
    PerfilSaude perfil;
    int idade;
    float freqMax, freqIdeal, imc;
    int n, i;

    printf("Digite o número de perfis de saúde a serem inseridos: ");
    scanf("%d", &n);
    PerfilSaude *perfis = (PerfilSaude *)malloc(n * sizeof(PerfilSaude));

    for (i = 0; i < n; i++) {
        printf("\nDigite o nome completo: ");
        scanf(" %[^\n]s", perfis[i].nome);
        printf("Digite o sexo (M/F): ");
        scanf(" %c", &perfis[i].sexo);
        printf("Digite a data de nascimento (dia mes ano): ");
        scanf("%d %d %d", &perfis[i].dataNascimento.dia, &perfis[i].dataNascimento.mes, &perfis[i].dataNascimento.ano);
        printf("Digite a altura (em metros): ");
        scanf("%f", &perfis[i].altura);
        printf("Digite o peso (em kg): ");
        scanf("%f", &perfis[i].peso);

        calcularIdade(&perfis[i], &idade);
        calcularFrequenciaCardiaca(&perfis[i], idade, &freqMax, &freqIdeal);
        imc = calcularIMC(&perfis[i]);

        printf("\nInformações do perfil de saúde:\n");
        exibirPerfil(&perfis[i]);
        printf("Idade: %d anos\n", idade);
        printf("IMC: %.2f\n", imc);
        printf("Frequência cardíaca máxima: %.2f bpm\n", freqMax);
        printf("Frequência cardíaca ideal: %.2f bpm\n", freqIdeal);

        // Exibição da tabela de valores do IMC
        printf("\nTabela de valores do IMC:\n");
        printf("Menor que 18.5: Abaixo do peso\n");
        printf("Entre 18.5 e 24.9: Peso normal\n");
        printf("Entre 25 e 29.9: Sobrepeso\n");
        printf("30 ou maior: Obesidade\n");

        // Calcular expectativa de vida baseado na expectativa de vida da população
        int expectativaVida = (perfis[i].sexo == 'M' || perfis[i].sexo == 'm') ? 76 : 82; // Exemplo: expectativa de vida
        int anosRestantes = expectativaVida - idade;
        printf("Expectativa de anos restantes de vida: %d anos\n", anosRestantes);
    }

    free(perfis);

    return 0;
}
