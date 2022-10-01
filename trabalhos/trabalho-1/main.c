#include <stdio.h>
#include "wine.h"
#include "catalog.h"

int main (void){
     CATALOG *catalog = new_catalog("vinho.csv");
     if(catalog!=NULL)
     {
        catalog_print(catalog);
        delete_catalog(&catalog);
     }
     
    return 0;
}