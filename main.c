// Turma: 33C
// Nome: Gabriel Robert Wischer Guedes
// Matrícula: 2211784

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct biodata
{
    float altura;
    float peso;
};
typedef struct biodata bioData;
struct Paciente
{
    char* nome[81];
    bioData BIODATA;
};
typedef struct Paciente paciente;

int compAltura(float a, paciente* b)
{
    if (a < b->BIODATA.altura)
        return -1;
    else if (a > b->BIODATA.altura)
        return 1;
    else
        return 0;
}

int tamanhoArq(char* aqruivo)
{
    FILE* arq = fopen("pacientes.txt", "r");
    if (arq == NULL)
    {
        fclose(arq);
        return -1;
    }
    int tamanho = 0;

    while (!feof(arq))
    {
        fscanf(arq, " %*[^\n]");
        tamanho++;
    }

    return tamanho;
}

paciente* pacienteVetor(char* arquivo, int qtdLinhas)
{
    FILE* arq = fopen("pacientes.txt", "r");
    if (arq == NULL)
    {
        fclose(arq);
        return NULL;
    }

    paciente* pessoa = (paciente*)malloc(sizeof(paciente) * qtdLinhas);
    if (pessoa == NULL)
    {
        fclose(arq);
        return NULL;
    }

    int i = 0;
    while (i < qtdLinhas)
    {
        fscanf(arq, " %[^:]: %f %f", pessoa[i].nome, &pessoa[i].BIODATA.altura, &pessoa[i].BIODATA.peso);
        i++;
    }

    fclose(arq);
    return pessoa;
}

void printPaciente(paciente* pessoa, int qtdLinhas)
{
    for (int i = 0; i < qtdLinhas; i++)
    {
        printf("%s\t\t%.2f %.1f\n", pessoa[i].nome, pessoa[i].BIODATA.altura, pessoa[i].BIODATA.peso);
    }
}

float calculaModa(paciente* pessoa, int qtdLinhas)
{
    if (qtdLinhas == 0)
        return -1;

    float moda = pessoa[0].BIODATA.altura;
    int contModa = 0;

    for (int i = 0; i < qtdLinhas; i++)
    {
        float alturaAtual = pessoa[i].BIODATA.altura;
        int contAtual = 0;

        while (i < qtdLinhas && pessoa[i].BIODATA.altura == alturaAtual)
        {
            contAtual++;
            i++;
        }

        if (contAtual >= contModa)
        {
            moda = alturaAtual;
            contModa = contAtual;
        }
    }

    return moda;
}

int buscaPesoMaior(int qtdLinhas, paciente* pessoa, float altura)
{
    int ini = 0;
    int fim = qtdLinhas - 1;
    int meio, comp;

    while (ini <= fim)
    {
        meio = (ini + fim) / 2;
        comp = compAltura(altura, &pessoa[meio]);
        if (comp == 0)
        {
            while (meio > 0 && compAltura(altura, &pessoa[meio + 1]) == 0)
                meio++;
            return meio;
        }
        else if (comp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}

int main(void)
{
    char* arquivo = "pacientes.txt";
    int qtdLinhas = tamanhoArq(arquivo);
    if (qtdLinhas == -1)
    {
        printf("Falha ao abrir o arquivo.\n");
        return 1;
    }

    paciente* pessoas = pacienteVetor(arquivo, qtdLinhas);
    if (pessoas == NULL)
    {
        printf("Falha na alocação de memória ou na abertura do arquivo.\n");
        return 1;
    }

    printf("Pacients:\n");
    printPaciente(pessoas, qtdLinhas);

    float moda = calculaModa(pessoas, qtdLinhas);
    printf("\nModa: %.2f\n", moda);

    // Usando a moda
    int indiceModa = buscaPesoMaior(qtdLinhas, pessoas, moda);
    char** nomeModa = pessoas[indiceModa].nome;
    float alturaModa = pessoas[indiceModa].BIODATA.altura;
    float pesoModa = pessoas[indiceModa].BIODATA.peso;
    printf("Registro de maior peso com altura %.2f:\t%s %.2f %.1f\n", moda, nomeModa, alturaModa, pesoModa);

    // Usando 1.47
    int indiceAleatorio = buscaPesoMaior(qtdLinhas, pessoas, 1.47);
    char** nomeAleatorio = pessoas[indiceAleatorio].nome;
    float alturaAleatorio = pessoas[indiceAleatorio].BIODATA.altura;
    float pesoAleatorio = pessoas[indiceAleatorio].BIODATA.peso;
    printf("Registro de maior peso com altura %.2f:\t%s %.2f %.1f\n", 1.47, nomeAleatorio, alturaAleatorio, pesoAleatorio);

    // Usando 1.97
    int indiceUltimo = buscaPesoMaior(qtdLinhas, pessoas, 1.97);
    char** nomeUltimo = pessoas[indiceUltimo].nome;
    float alturaUltimo = pessoas[indiceUltimo].BIODATA.altura;
    float pesoUltimo = pessoas[indiceUltimo].BIODATA.peso;
    printf("Registro de maior peso com altura %.2f:\t%s %.2f %.1f\n", 1.97, nomeUltimo, alturaUltimo, pesoUltimo);

    // Usando altura que não tem no arquivo
    if (buscaPesoMaior(qtdLinhas, pessoas, 2.10) == -1)
        printf("Não há registro com altura %.2f\n", 2.10);

    free(pessoas);
    return 0;
}