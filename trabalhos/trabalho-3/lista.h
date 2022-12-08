#ifndef LISTA_H
#define LISTA_H

#include "aluno.h"
#include <string.h>

#define TAM_MAX 100 /*estimativa do tamanho máximo da valores*/
#define INICIO 0
#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct lista LISTA;

LISTA *lista_criar();
boolean lista_vazia(const LISTA *lista);
int lista_tamanho(const LISTA *lista);
int lista_inserir(LISTA *lista, ALUNO *aluno);
ALUNO *lista_busca_sequencial(const LISTA *lista, char *chave);
boolean lista_remover_aluno(LISTA *lista, char *chave);
#endif //LISTA_H
