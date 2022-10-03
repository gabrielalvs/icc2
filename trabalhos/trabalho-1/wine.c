#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wine.h"

struct wine_st
{   int id;
    double citric_acid;
    double residual_sugar;
    double density;
    double pH;
    double alcohol;
};

WINE *new_wine (int id, double citric_acid, double residual_sugar, double density, double pH, double alcohol)
{
    WINE *wine;

    wine = (WINE *) malloc(sizeof(WINE));

    if (wine != NULL)
    {
        wine->id = id;
        wine->citric_acid = citric_acid;
        wine->residual_sugar = residual_sugar;
        wine->density = density;
        wine->pH = pH;
        wine->alcohol = alcohol;
        return wine;
    }
    return NULL;
}

boolean wine_delete(WINE **wine)
{
    if (*wine != NULL)
    {
        (*wine)->id = ERRO; /*apaga o item simbolicamente*/
        free (*wine);
        *wine = NULL;
        return TRUE;
    }
    return FALSE;
}

int wine_get_id(const WINE *wine)
{
    if (wine != NULL)
    {
        return wine->id;
    }
    return ERRO;
}


boolean wine_set_id(WINE *wine, int id)
{
    if (wine != NULL){
        wine->id = id;
        return TRUE;
    }
    return FALSE;
}


void wine_print(const WINE *wine)
{
    if (wine != NULL)
    {
        printf("ID: %d, Citric Acid: %.5f, Residual Sugar %.5f, Density %.5f, pH %.5f, Alcohol %.5f\n",
        wine->id, wine->citric_acid, wine->residual_sugar,
        wine->density, wine->pH, wine->alcohol);
    }
}

double wine_get_caract(const WINE *wine, int id_catact)
{
    if (wine != NULL)
    {
        switch (id_catact) {
        case 1:
            return wine->citric_acid;
            break;
        case 2:
            return wine->residual_sugar;
            break;
        case 3:
            return wine->density;
            break;
        case 4:
            return wine->pH;
            break;
        case 5:
            return wine->alcohol;
            break;
        }
    }
    return ERRO;
}
