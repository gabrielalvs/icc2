#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aluno.h"

struct aluno_st
{
    char nome[30];
    int *notas; 
    int n_notas_add;
    float media;
};

ALUNO *aluno_criar (const char *nome, int n_notas)
{
    ALUNO *aluno;

    aluno = (ALUNO *) malloc(sizeof(ALUNO));

    if (aluno != NULL)
    {
        strcpy(aluno->nome, nome);
        aluno->notas = (int *) malloc(sizeof(int)*(n_notas));
        aluno->notas[0] = 0;
        aluno->n_notas_add = 0;
        aluno->media = 0;
        return aluno;
    }
    return NULL;
}

boolean aluno_apagar(ALUNO **aluno)
{
    if (*aluno != NULL)
    {
        free((*aluno)->notas);
        free (*aluno);
        *aluno = NULL;
        return TRUE;
    }
    return FALSE;
}

boolean aluno_set_nota(ALUNO *aluno, int nota)
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
        printf("\n-->nome: %s", aluno->nome);
        
        /*for (int i = 0; i < aluno->n_notas_add; i++)
        {
            printf("\n-->notas: %d", aluno->notas[i]);
        }*/
        printf("\n-->media: %f \n", aluno->media);
    }
}

void aluno_media(ALUNO *aluno)
{
    if (aluno != NULL)
    {
        for (int i = 0; i < aluno->n_notas_add; i++)
        {
            aluno->media += aluno->notas[i];
        }

        aluno->media /= aluno->n_notas_add;
    }
}


int  aluno_get_nNotas(const ALUNO *aluno){
    if (aluno != NULL)
    {
        return aluno->n_notas_add;
    }
    return ERRO;
}

float  aluno_get_media(const ALUNO *aluno){
    if (aluno != NULL)
    {
        return aluno->media;
    }
    return ERRO;
}

int  aluno_get_nota(const ALUNO *aluno, int index){
    if (aluno != NULL)
    {
        return aluno->notas[index];
    }
    return ERRO;
}

char *aluno_get_nome(ALUNO *aluno)
{
    if (aluno != NULL)
    {
       return aluno->nome;
    }

    return NULL;
}