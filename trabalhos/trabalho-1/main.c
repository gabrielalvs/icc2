/**
   Gabriel Lima Alves
   nºUSP: 12558537
   SCC0201 - ICC2
**/

#include <stdio.h>
#include <string.h>
#include "wine.h"
#include "catalog.h"

int main (void){

   char nfile[ 50 ];
   scanf ( "%s" , nfile);

   CATALOG *catalog = new_catalog(nfile);

   if(catalog==NULL)
   {
      return 0;
   }

   int nopcao = 0;
   char nm_caract[ 20 ];
   int id_catact;
   double param;

   scanf ( "%i" , &nopcao);

   for (int i = 0; i < nopcao; i++)
   {
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

      search(catalog,id_catact,param);


   }

   delete_catalog(&catalog);
   return 0;
}