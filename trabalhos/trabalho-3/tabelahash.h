#ifndef TABELAHASH_H
#define TABELAHASH_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct tabelahash_st TABELAHASH;

TABELAHASH *tabelahash_criar (const int tamanho);
unsigned int hash(char *s);
#endif //TABELAHASH_H
