#include <stdio.h>
#include <string.h>
#include "wine.h"
#include "catalog.h"

int main (void){

   char nfile[ 50 ];
   //printf("digite nome do arquivo\n");
   scanf ( "%s" , nfile);

   CATALOG *catalog = new_catalog(nfile);

   if(catalog==NULL)
   {
      return 0;
   }

   //catalog_print(catalog);

   int nopcao = 0;
   char nm_caract[ 20 ];
   int id_catact;
   double param;

   //printf("digite o número de opções\n");
   scanf ( "%i" , &nopcao);

   for (int i = 0; i < nopcao; i++)
   {
      //printf("digite o nome da caracteristica e valor\n");
      scanf ("%s  %lf" , nm_caract, &param);

      if (strcmp(nm_caract, "citric_acid") == 0) 
      {
         id_catact = 1;
      } 
      else if (strcmp(nm_caract, "residual_sugar") == 0)
      {
         id_catact = 2;
      }
      else if (strcmp(nm_caract, "density") == 0)
      {
         id_catact = 3;
      }      
      else if (strcmp(nm_caract, "pH") == 0)
      {
         id_catact = 4;
      }
      else if (strcmp(nm_caract, "alcohol") == 0)
      {
         id_catact = 5;
      }

      //printf("%i  %lf \n" , id_catact, param);
      search(catalog,id_catact,param);


   }

   delete_catalog(&catalog);
   return 0;
}