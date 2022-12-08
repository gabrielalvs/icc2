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