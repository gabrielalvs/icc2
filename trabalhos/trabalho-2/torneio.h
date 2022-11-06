#ifndef TORNEIO_H
#define TORNEIO_H

#include "diario.h"

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct torneio_st TORNEIO;

boolean torneio_apagar(TORNEIO **torneio);
boolean torneio_ordenar(DIARIO *diario);
#endif //TORNEIO_H
