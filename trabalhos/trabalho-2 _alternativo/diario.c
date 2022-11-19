#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "diario.h"

struct diario_st
{
    ALUNO **alunos;
    int n_alunos_add;
    int n_alunos;
    int n_notas;
};

DIARIO *diario_criar(int n_alunos, int n_notas)
{
    DIARIO *diario;

    diario = (DIARIO *) malloc(sizeof(DIARIO));

    if (diario != NULL)
    {
        diario->n_alunos = n_alunos;
        diario->n_notas = n_notas;
        diario->n_alunos_add = 0;
        diario->alunos = (ALUNO **) malloc( diario->n_alunos * sizeof(ALUNO*));

        return diario;
    }
    return NULL;
}

boolean diario_apagar(DIARIO **diario)
{
    if (*diario != NULL){
        for(int i = 0; i < (*diario)->n_alunos; i++){
            if((*diario)->alunos[i] != NULL){
               aluno_apagar(&((*diario)->alunos[i]));
            }
        }
        free((*diario)->alunos);
        free(*diario);
        *diario = NULL;
        return TRUE;
    }   

    return FALSE;
}

boolean diario_set_aluno(DIARIO *diario, ALUNO *aluno)
{
    if (diario != NULL){
        diario->alunos[diario->n_alunos_add] = aluno;
        diario->n_alunos_add++;
        return TRUE;
    }
    return FALSE;
}

boolean diario_alterar_aluno(DIARIO *diario, ALUNO *aluno, int index)
{
    if (diario != NULL){
        diario->alunos[index] = aluno;
        return TRUE;
    }
    return FALSE;
}

void diario_imprimir(const DIARIO *diario)
{
    if (diario != NULL)
    {
        for(int i = 0; i < diario->n_alunos; i++){
            if(diario->alunos[i] != NULL){
               aluno_imprimir(diario->alunos[i]);
            }
        }
    }
}

int diario_get_nAlunos(const DIARIO *diario)
{
    if (diario != NULL)
    {
        return diario->n_alunos;
    }
    return ERRO;
}

int diario_get_nNotas(const DIARIO *diario)
{
    if (diario != NULL)
    {
        return diario->n_notas;
    }
    return ERRO;
}

ALUNO *diario_get_aluno(const DIARIO *diario, int index)
{
    if (diario != NULL)
    {
        return diario->alunos[index];
    }
    return NULL;
}