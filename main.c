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
        printf("%s: %.2f %.1f\n", pessoa[i].nome, pessoa[i].BIODATA.altura, pessoa[i].BIODATA.peso);
    }
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
    
    free(pessoas);
    return 0;
}