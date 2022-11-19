#ifndef DIARIO_H
#define DIARIO_H

#include "aluno.h"
#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct diario_st DIARIO;

DIARIO *diario_criar(int n_alunos, int n_notas);
boolean diario_apagar(DIARIO **diario);
void diario_imprimir(const DIARIO *diario);
boolean diario_set_aluno(DIARIO *diario, ALUNO *aluno);
int diario_get_nAlunos(const DIARIO *diario);
int diario_get_nNotas(const DIARIO *diario);
ALUNO *diario_get_aluno(const DIARIO *diario, int index);
boolean diario_alterar_aluno(DIARIO *diario, ALUNO *aluno, int index);

#endif //DIARIO_H
