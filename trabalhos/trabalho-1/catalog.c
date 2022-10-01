#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "catalog.h"
#include "wine.h"

struct catalog_st
{   
    WINE **wines;
    int n_elements;
    int n_vinhos;
};

CATALOG *new_catalog (const char *nfile)
{
    CATALOG *catalog = (CATALOG *) malloc(sizeof(CATALOG));

    catalog->n_vinhos = 0;

    catalog->n_elements = 100;
    catalog->wines= (WINE **) malloc(catalog->n_elements * sizeof(WINE*));

    if (catalog != NULL)
    {
        if(set_wines_file(catalog, nfile) != TRUE){
            return NULL;
            
        }

        return catalog;
    }
    return NULL;

    
}

boolean delete_catalog(CATALOG **catalog)
{
    if (*catalog != NULL){
        for(int i = 0; i < (*catalog)->n_vinhos; i++){
            if(get_wine(*catalog, i) != NULL){
                free(get_wine(*catalog, i));
            }
        }
        free((*catalog)->wines);
        free(*catalog);
        *catalog = NULL;
        return TRUE;
    }   

    return FALSE;
}

WINE *get_wine(const CATALOG *catalog, int index){
    return catalog->wines[index];
}

int get_num_wines(const CATALOG *catalog){
    return catalog->n_vinhos;
}

/*void set_num_wines(CATALOG *catalog, int i){
    catalog->n_vinhos = i;
}

int get_n_elements(const CATALOG *catalog){
    return catalog->n_elements;
}

void set_n_elements(CATALOG *catalog, int i){
    catalog->n_elements = i;
}*/

WINE **get_list_wine(const CATALOG *catalog){
    return catalog->wines;
}

boolean set_wines_file(CATALOG *catalog, const char *nfile)
{   
    int id;
    double citric_acid;
    double residual_sugar;
    double density;
    double pH;
    double alcohol;

    FILE *file = fopen(nfile, "r");

    if (file == NULL)
    { 
        return FALSE;
    }
    char line[80];

    fscanf(file, "%[^\n]", line);
    fgetc(file);

    while ((fscanf(file, "%[^\n]", line))!= EOF)
    {
        
        fgetc(file); // Reads in '\n' character and moves file
        // stream past delimiting character
        sscanf(line, "%d,%lf,%lf,%lf,%lf,%lf", &id, &citric_acid, &residual_sugar, &density, &pH, &alcohol);

        if (set_wine(catalog, new_wine(id, citric_acid, residual_sugar, density, pH, alcohol))!=TRUE)
        {
            return FALSE;
        }

        if (ferror(file))
        {
            return FALSE;
        }
    }

  fclose(file);
  return TRUE;
}

boolean set_wine(CATALOG *catalog, WINE *wine)
{
    if(wine != NULL)
    {
        if(catalog->n_vinhos ==catalog->n_elements){
            catalog->n_elements *= 2; 
            WINE **temp = (WINE **) realloc(get_list_wine(catalog), sizeof(WINE*) * catalog->n_elements);
            if(temp!=NULL)
            {   
                catalog->wines = temp;
                catalog->wines[catalog->n_vinhos] = wine;
            }else{
                return FALSE;
            }
        }else{
            catalog->wines[catalog->n_vinhos] = wine;
        }
        catalog->n_vinhos++;
    }else{
        return FALSE;
    }
    return TRUE;
}

void catalog_print(const CATALOG *catalog)
{
    for(int i = 0; i < catalog->n_vinhos; i++){
        if(get_wine(catalog, i) != NULL){
            wine_print(get_wine(catalog, i));
        }
    }
}