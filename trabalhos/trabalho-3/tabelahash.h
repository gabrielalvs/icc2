#ifndef TABELAHASH_H
#define TABELAHASH_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct tabelahash_st TABELAHASH;

TABELAHASH *tabelahash_criar (const int tamanho);
unsigned int hash(char *s);
unsigned int indexar(unsigned int x);
boolean tabelahash_set_aluno(TABELAHASH *tabelahash, ALUNO *aluno);
ALUNO *tabelahash_get_aluno(TABELAHASH *tabelahash, char *s);
boolean tabelahash_apagar(TABELAHASH **tabelahash);
int tabelahash_logar(TABELAHASH *tabelahash, char *nusp, unsigned int senha);
#endif //TABELAHASH_H
