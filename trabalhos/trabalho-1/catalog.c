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

void search(CATALOG *catalog, const int id_catact, const double param)
{
    if(catalog!=NULL)
    {   
        //printf("%i  %lf \n" , id_catact, param);
        wines_Sort(catalog, id_catact);
        //catalog_print(catalog);
        int index = buscaBinaria_wines(catalog, id_catact, param);
        if(index==-1){
            printf("Nenhum vinho encontrado\n");
        return;
        }

        int i = index +1;
        while(wine_get_caract(catalog->wines[index], id_catact) == wine_get_caract(catalog->wines[i], id_catact))i++;
        wine_print(catalog->wines[index]);
        printf("Total de vinhos encontrados: %d\n", i-index);
    }
}

/*void wines_Sort(CATALOG *catalog, const int id_catact)
{
    int tamanho = catalog->n_vinhos;
    	int j; //indica o elemento atual
	for(j = tamanho-2; j >= 0; j--){//o elemento na posição final não precisa analisar
		WINE *wine = catalog->wines[j];
		int i = j + 1; //armazenar a posição de análise (posterior ao j até o fim do vetor)
		
		//início && valor atual é menor que a chave de análise || igual com id menor
		while (i <= tamanho-1 && 
        ((wine_get_caract(catalog->wines[i],id_catact) < wine_get_caract(wine,id_catact)) 
            ||  (wine_get_caract(catalog->wines[i],id_catact) == wine_get_caract(wine,id_catact) 
                && (wine_get_id(catalog->wines[i]) < wine_get_id(wine)))))
        {
            catalog->wines[i-1] = catalog->wines[i];
			i++;
		}
        catalog->wines[i-1] = wine; //posiciona a chave na posição correta
	}
}*/

void wines_Sort(CATALOG *catalog, const int id_catact){
    int tamanho = catalog->n_vinhos-1;
    int pos;
    

    for(int j = 0; j<=tamanho;j++)
    {   
        WINE *wine;
        pos = 0 ;
        for(int i = 1; i<=tamanho-j; i++)
        {
            wine = catalog->wines[pos];
            if((wine_get_caract(catalog->wines[i],id_catact)>wine_get_caract(wine,id_catact)) 
            || (wine_get_caract(catalog->wines[i],id_catact) == wine_get_caract(wine,id_catact)
                && wine_get_id(catalog->wines[i]) > wine_get_id(wine)))
            {
                pos = i;
            }
        }
        wine = catalog->wines[tamanho-j];
        catalog->wines[tamanho-j] = catalog->wines[pos];
        catalog->wines[pos] = wine;
    }
}

int buscaBinaria_wines(CATALOG *catalog,const int id_catact, const double param){
    int posicaoInicial = 0 ;
    int posicaoFinal = catalog->n_vinhos-1;
    int resultado = -1;

	while(posicaoInicial <= posicaoFinal){ //log n
		int centro = (int)((posicaoInicial+posicaoFinal)/2);
    
		if (param == wine_get_caract(catalog->wines[centro], id_catact)){ 
			resultado = centro;
            posicaoFinal = centro - 1;
        }
		if (param < wine_get_caract(catalog->wines[centro], id_catact)){ //se o número existir estará na primeira metade
			posicaoFinal = centro - 1;
        }
		if (param > wine_get_caract(catalog->wines[centro], id_catact)){ //se o número existir estará na segunda metade
			posicaoInicial = centro + 1;
        }
	}
	return resultado;//valor não encontrado
}