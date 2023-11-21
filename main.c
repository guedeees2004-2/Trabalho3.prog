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

int compFloat(paciente* a, paciente* b)
{
    if (a->BIODATA.altura < b->BIODATA.altura)
        return -1;
    else if (a->BIODATA.altura > b->BIODATA.altura)
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

    while(!feof(arq))
    {
        fscanf(arq, " %*[^\n]");
        tamanho++;
    }

    return tamanho;
}

paciente* pacienteVetor(char* arquivo, int qtdLinhas)
{
    FILE* arq = fopen("pacientes.txt", "r");
    if(arq == NULL)
    {
        fclose(arq);
        return NULL;
    }
    
    paciente* pessoa = (paciente*) malloc(sizeof(paciente) * qtdLinhas);
    if (pessoa == NULL)
    {
        fclose(arq);
        return NULL;
    }

    int i = 0;
    while(i < qtdLinhas)
    {
        fscanf(arq, " %[^:]: %f %f", pessoa[i].nome, &pessoa[i].BIODATA.altura, &pessoa[i].BIODATA.peso);
        i++;
    }

    fclose(arq);
    return pessoa;
}

void printPaciente(paciente* pessoa, int qtdLinhas)
{
    for(int i = 0; i < qtdLinhas; i++)
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
    paciente auxiliar;
    auxiliar.BIODATA.altura = altura;


    while (ini <= fim)
    {
        meio = (ini + fim)/2;
        comp = compFloat(&auxiliar, &pessoa[meio]);
        if (comp == 0)
        {
            while (meio > 0 && compFloat(&auxiliar, &pessoa[meio +1]) == 0)
                meio++;
            return meio;
        }
        else if (comp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

int main(void)
{
    char* arquivo = "pacientes.txt";
    int qtdLinhas = tamanhoArq(arquivo);
    if(qtdLinhas == -1)
    {
        printf("Falha ao abrir o arquivo.\n");
        return 1;
    }

    paciente* pessoas = pacienteVetor(arquivo, qtdLinhas);
    if(pessoas == NULL)
    {
        printf("Falha na alocação de memória ou na abertura do arquivo.\n");
        return 1;
    }

    printf("Pacients:\n");
    printPaciente(pessoas, qtdLinhas);
    
    float moda = calculaModa(pessoas, qtdLinhas);
    printf("Moda: %.2f\n", moda);

    // Usando a moda
    printf("Registro de maior peso com altura %.2f:\t%s %.2f %.1f\n", moda, pessoas[buscaPesoMaior(qtdLinhas, pessoas, moda)].nome, pessoas[buscaPesoMaior(qtdLinhas, pessoas, moda)].BIODATA.altura, pessoas[buscaPesoMaior(qtdLinhas, pessoas, moda)].BIODATA.peso);

    // Usando 1.47
    printf("Registro de maior peso com altura %.2f:\t%s %.2f %.1f\n", 1.47, pessoas[buscaPesoMaior(qtdLinhas, pessoas, 1.47)].nome, pessoas[buscaPesoMaior(qtdLinhas, pessoas, 1.47)].BIODATA.altura, pessoas[buscaPesoMaior(qtdLinhas, pessoas, 1.47)].BIODATA.peso);

    // Usando 1.97
    char* nome = pessoas[buscaPesoMaior(qtdLinhas, pessoas, 1.97)].nome;
    float altura = pessoas[buscaPesoMaior(qtdLinhas, pessoas, 1.97)].BIODATA.altura;
    float peso = pessoas[buscaPesoMaior(qtdLinhas, pessoas, 1.97)].BIODATA.peso;
    printf("Registro de maior peso com altura %.2f:\t%s %.2f %.1f\n", 1.97, nome, altura, peso);

    free(pessoas);
    return 0;
}