#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aluno.h"

struct aluno_st
{
    char nusp[10];
    float notas[4]; 
    int n_notas_add;
    unsigned int senha;
};

ALUNO *aluno_criar (const char *nusp, unsigned int senha)
{
    ALUNO *aluno;

    aluno = (ALUNO *) malloc(sizeof(ALUNO));

    if (aluno != NULL)
    {
        strcpy(aluno->nusp, nusp);
        aluno->n_notas_add = 0;
        aluno->senha = senha;
        return aluno;
    }
    return NULL;
}

boolean aluno_apagar(ALUNO **aluno)
{
    if (*aluno != NULL)
    {
        free (*aluno);
        *aluno = NULL;
        return TRUE;
    }
    return FALSE;
}

boolean aluno_set_nota(ALUNO *aluno, float nota)
{
    if (aluno != NULL){
        aluno->notas[aluno->n_notas_add] = nota;
        aluno->n_notas_add++;
        return TRUE;
    }
    return FALSE;
}


void aluno_imprimir(const ALUNO *aluno)
{
    if (aluno != NULL)
    {
        printf("\n-->nusp: %s", aluno->nusp);
    }
}

void aluno_imprimir_notas(const ALUNO *aluno)
{
    if (aluno != NULL)
    {
        printf("Notas: P1=%.1lf, P2=%.1lf, T1=%.1lf, T2=%.1lf \n", aluno->notas[0],aluno->notas[1],aluno->notas[2],aluno->notas[3]);
    }
}

int  aluno_get_nNotas(const ALUNO *aluno)
{
    if (aluno != NULL)
    {
        return aluno->n_notas_add;
    }
    return ERRO;
}

int  aluno_get_nota(const ALUNO *aluno, int index)
{
    if (aluno != NULL)
    {
        return aluno->notas[index];
    }
    return ERRO;
}

char *aluno_get_nusp(ALUNO *aluno)
{
    if (aluno != NULL)
    {
       return aluno->nusp;
    }

    return NULL;
}

unsigned int aluno_get_senha(ALUNO *aluno)
{
    if (aluno != NULL)
    {
       return aluno->senha;
    }

    return 0;
}