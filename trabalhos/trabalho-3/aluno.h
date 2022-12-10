#ifndef ALUNO_H
#define ALUNO_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct aluno_st ALUNO;

ALUNO *aluno_criar (const char *nusp, unsigned int senha);
boolean aluno_apagar(ALUNO **aluno);
boolean aluno_set_nota(ALUNO *aluno, float nota);
void aluno_imprimir(const ALUNO *aluno);
int  aluno_get_nNotas(const ALUNO *aluno);
int  aluno_get_nota(const ALUNO *aluno, int index);
char *aluno_get_nusp(ALUNO *aluno);
void aluno_imprimir_notas(const ALUNO *aluno);
unsigned int aluno_get_senha(ALUNO *aluno);
#endif //ALUNO_H
