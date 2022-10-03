#ifndef WINE_H
#define WINE_H

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000

typedef struct wine_st WINE;

WINE *new_wine (int id, double citric_acid, double residual_sugar, double density, double pH, double alcohol);
boolean wine_delete(WINE **wine);
void wine_print(const WINE *wine);
int wine_get_id(const WINE *wine);
boolean wine_set_id(WINE *wine, int id);
double wine_get_caract(const WINE *wine, int id_catact);

#endif //WINE_H
