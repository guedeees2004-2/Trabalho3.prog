#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Paciente
{
    char* nome[81];
    float altura;
    float peso;
};
typedef struct Paciente paciente;

int tamanhoArq(char* aqruivo)
{
    FILE* arq = fopen("pacientes.txt", "r");
    if (arq == NULL)
        return -1;
    int tamanho = 0;
    int np;

    while(!feof(arq))
    {
        np = fscanf(arq, " %*[^\n]");
        tamanho++;
    }

    return tamanho;
}

paciente* pacienteVetor(char* arquivo, int qtdLinhas)
{
    FILE* arq = fopen("pacientes.txt", "r");
    if(arq == NULL)
        return NULL;
    
    paciente* pessoa = (paciente*) malloc(sizeof(paciente) * qtdLinhas);
    int i = 0;

    while(i < qtdLinhas)
    {
        fscanf(arq, " %[^:]: %f %f", &pessoa[i].nome, &pessoa[i].altura, &pessoa[i].peso);
        i++;
    }

    fclose(arq);
    return pessoa;
}

void printPaciente(paciente* pessoa)
{
    printf("%s: %.2f %.1f\n", pessoa->nome, pessoa->altura, pessoa->peso);
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
    for(int i = 0; i < qtdLinhas; i++)
    {
        printPaciente(&pessoas[i]);
    }
    
    free(pessoas);
    return 0;
}