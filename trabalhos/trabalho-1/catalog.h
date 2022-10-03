#ifndef CATALOG_H
#define CATALOG_H


#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000
#include "wine.h"

typedef struct catalog_st CATALOG;

CATALOG *new_catalog (const char *file);

boolean delete_catalog(CATALOG **catalog);

void catalog_print(const CATALOG *catalog);

WINE *get_wine(const CATALOG *catalog, int index);

WINE **get_list_wine(const CATALOG *catalog);

boolean set_wines_file(CATALOG *catalog, const char *file);

boolean set_wine(CATALOG *catalog, WINE *wine);

/*int get_n_elements(const CATALOG *catalog);

void set_n_elements(CATALOG *catalog, int i);

void set_num_wines(CATALOG *catalog, int i);*/

int get_num_wines(const CATALOG *catalog);

void search(CATALOG *catalog, const int id_catact,const  double param);

void wines_Sort(CATALOG *catalog, const int id_catact);

int buscaBinaria_wines(CATALOG *catalog, const int id_catact, const double param);

#endif //CATALOG_H
