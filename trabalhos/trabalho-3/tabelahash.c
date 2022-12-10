#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "lista.h"
#include "tabelahash.h"

struct tabelahash_st
{
    LISTA **tabela;
    int tamanho;
};

/*static void bin(unsigned n){
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n");
}*/

TABELAHASH *tabelahash_criar (const int tamanho)
{
    TABELAHASH *tabelahash = (TABELAHASH*) malloc(sizeof(TABELAHASH));

    tabelahash->tamanho = tamanho;

    if (tabelahash != NULL)
    {
        tabelahash->tabela = (LISTA **) malloc(tamanho * sizeof(LISTA*));

        for (int i = 0; i < tamanho; i++)
        {
           tabelahash->tabela[i] = NULL;
        }
        
        return tabelahash;
    }
    return NULL;
}

unsigned int hash(char *s){
    unsigned short int low = 0;
    unsigned short int high = 1; 

    for (int i = 0; i < strlen(s); i++)
    {
        low = (low + s[i])%65521;
        high = (high + low)%65521;
    }

    unsigned int resultado = (high << 16) + low;

    return resultado;
}

unsigned int indexar(unsigned int x){
    return (x & 15)+((x >> 28) & 15);
}


boolean tabelahash_set_aluno(TABELAHASH *tabelahash, ALUNO *aluno)
{

    if (tabelahash != NULL){

        unsigned int index = indexar(hash(aluno_get_nusp(aluno)));
        
        if (tabelahash->tabela[index] == NULL)
        {
            tabelahash->tabela[index] = lista_criar();
            printf("Cadastro efetuado com sucesso \n");
            return lista_inserir(tabelahash->tabela[index],aluno);
        }

        if(tabelahash_get_aluno(tabelahash,aluno_get_nusp(aluno)) == NULL)
        {
            printf("Cadastro efetuado com sucesso \n");
            return lista_inserir(tabelahash->tabela[index],aluno);
        }
        
    }
    printf("NUSP ja cadastrado \n");
    return FALSE;
}

ALUNO *tabelahash_get_aluno(TABELAHASH *tabelahash, char *s)
{
    if (tabelahash != NULL){
        return lista_busca_sequencial(tabelahash->tabela[indexar(hash(s))],s);
    }

    return NULL;
}

boolean tabelahash_apagar(TABELAHASH **tabelahash)
{
    if (*tabelahash != NULL)
    {   
        for (int i = 0; i < (*tabelahash)->tamanho; i++)
        {
            if ((*tabelahash)->tabela[i] != NULL)
            {
               lista_apagar(&(*tabelahash)->tabela[i]);
            }
        }
        free ((*tabelahash)->tabela);
        (*tabelahash)->tabela = NULL;
        free (*tabelahash);
        *tabelahash = NULL;
        return TRUE;
    }
    return FALSE;
}

int tabelahash_logar(TABELAHASH *tabelahash, char *nusp, unsigned int senha)
{
    if (tabelahash != NULL)
    {   
        ALUNO *aluno = tabelahash_get_aluno(tabelahash,nusp);

        if (aluno!=NULL)
        {
            if (aluno_get_senha(aluno)==senha)
            {
                return 0;
            }
            return 1;
        }
        return 2;
    }
    return 3;
}


