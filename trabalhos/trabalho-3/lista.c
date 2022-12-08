#include <stdlib.h>
#include "lista.h"
#include "aluno.h"

typedef struct node_st NODE;

struct node_st
{
    ALUNO *aluno;
    NODE* proximo;
};

struct lista {
    NODE* inicio;
    NODE* fim;
    int tamanho;
};

LISTA *lista_criar()
{
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

boolean lista_vazia(const LISTA *lista)
{
    if(lista != NULL)
    {
        return lista->inicio == NULL;
    }
    return ERRO;
}

int lista_tamanho(const LISTA *lista)
{
    if(lista != NULL)
    {
        return lista->tamanho;
    }
    return ERRO;
}

int lista_inserir(LISTA *lista, ALUNO *aluno)
{
    if(lista != NULL)
    {
        NODE *novoNode = (NODE *) malloc(sizeof(NODE));
        if (novoNode != NULL) {
            novoNode->aluno = aluno;
            novoNode->proximo = NULL;
            if(lista_vazia(lista))
            {
                lista->inicio = novoNode;
            }
            else
            {
                lista->fim->proximo = novoNode;
            }
            lista->fim = novoNode;
            lista->tamanho++;
            return TRUE;
        }
    }
    return ERRO;
}

ALUNO *lista_busca_sequencial(const LISTA *lista, char *chave) {
    if (lista != NULL) {
        NODE *nodeAtual;
        nodeAtual = lista->inicio;
        while(nodeAtual != NULL)
        {
            if(strcmp(aluno_get_nusp(nodeAtual->aluno), chave) == 0)
            {
                return nodeAtual->aluno;
            }
            nodeAtual = nodeAtual->proximo;
        }
    }
    return NULL;
}

boolean lista_remover_aluno(LISTA *lista, char *chave) {
    if (lista != NULL) {
        NODE *nodeAtual;
        NODE *nodeAnterior = NULL;
        nodeAtual = lista->inicio;
        while(nodeAtual != NULL && strcmp(aluno_get_nusp(nodeAtual->aluno), chave) != 0)
        {
            nodeAnterior = nodeAtual;
            nodeAtual = nodeAtual->proximo;
        }
        if(nodeAtual != NULL)
        {
            if(nodeAtual == lista->inicio)
            {
                lista->inicio = nodeAtual->proximo;
            }
            else
            {
                nodeAnterior->proximo = nodeAtual->proximo;
            }
            nodeAtual->proximo = NULL;
            if(lista->fim == nodeAtual)
            {
                lista->fim = nodeAnterior;
            }
            lista->tamanho--;
            free(nodeAtual);
            nodeAtual = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

