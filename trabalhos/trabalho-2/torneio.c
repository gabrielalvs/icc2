#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "torneio.h"
#include "aluno.h"
#include "diario.h"


typedef struct competidor_st COMPETIDOR;

struct competidor_st
{
    ALUNO *aluno;
    int posicao_largada;
    int criterio_desempate;
};

struct torneio_st
{
    COMPETIDOR **competidores;
};

COMPETIDOR *competidor_criar (ALUNO *aluno, int posicao_largada)
{
    COMPETIDOR *competidor;

    competidor = (COMPETIDOR *) malloc(sizeof(COMPETIDOR));

    if (competidor != NULL)
    {
        competidor->aluno = aluno;
        competidor->posicao_largada = posicao_largada;
        competidor->criterio_desempate = 0;
        return competidor;
    }
    return NULL;
}

boolean torneio_apagar(TORNEIO **torneio)
{
    if (*torneio != NULL)
    {
        free (*torneio);
        *torneio = NULL;
        return TRUE;
    }
    return FALSE;
}


static boolean torneio_primeira_ordenacao(TORNEIO *torneio, int p_folhas, int t_arv, int n_notas);

static void torneio_imprimir_resultado(TORNEIO *torneio_resultado, int n_alunos);

static boolean torneio_n_ordenacoes(TORNEIO *torneio, int posicao_alterada, int profundidade);

static boolean torneio_comparar_competidores(TORNEIO *torneio, int aux);

static boolean torneio_preencher_resultado(TORNEIO *torneio_resultado, TORNEIO *torneio,  int quant_vencedores);

boolean torneio_ordenar(DIARIO *diario)
{   
    
    if (diario != NULL)
    {
        /* O tamanho do vetor que sera a estrutura da arvore binária é determinado a partir da profundidade da arvore 
        pela seguinte equação 2^(d+1) -1, em que d é a profundidade. Porém como foi oritado descartar a posição 0 do 
        vetor retira-se o -1. Já a profundidade de uma arvore binária é possível determinar sabendo a quantidade de 
        folhas, a equação que descreve isso é o teto de log2(n), em que n é o número de folhas.*/ 

        int profundidade = ceil(log2(diario_get_nAlunos(diario)));//produndidade da arvore
        int p_folhas = pow(2, profundidade );//quantidade de folhas 2^d, em que d é a profundiade
        int t_arv = (int) 2 * p_folhas;//quantidade de elementos da arvore
        
        TORNEIO *torneio;

        torneio = (TORNEIO *) malloc(sizeof(TORNEIO));

        torneio->competidores = (COMPETIDOR **) malloc( t_arv * sizeof(COMPETIDOR*));

        int quant_vencedores = 0;

        TORNEIO *torneio_resultado;

        torneio_resultado = (TORNEIO *) malloc(sizeof(TORNEIO));

        torneio_resultado->competidores = (COMPETIDOR **) malloc(diario_get_nAlunos(diario)* sizeof(COMPETIDOR*));

        /*Essa parte tem como função preencher as folhas da arvore, sabendo a quantidade total de nós as folhas vão ocupar 
        as p_folhas ultimas posiçoes*/ 
        int aux = 0; 
        for (int i = p_folhas; i < t_arv; i++)
        {   
            if(aux < diario_get_nAlunos(diario)){
                torneio->competidores[i] = competidor_criar(diario_get_aluno(diario,aux), i);
            }else{    
                torneio->competidores[i] = competidor_criar(aluno_criar_null(), i); 
            }
            aux++;
        }

        torneio_primeira_ordenacao(torneio, p_folhas, t_arv, diario_get_nNotas(diario));
        /*for (int i = 1; i < t_arv; i++)
        {
            aluno_imprimir(torneio->competidores[i]->aluno);
        }
        printf("\n--------------------------------------------------------------------------------------"); */

        int temp = torneio_preencher_resultado(torneio_resultado, torneio, quant_vencedores);
        for (int i = 0; i < diario_get_nAlunos(diario)-1; i++)//essa ordeção será feita o número de elmentos a serem ordenados -1   
        {
            quant_vencedores++;
            torneio_n_ordenacoes(torneio, temp, profundidade);
            /*for (int i = 1; i < t_arv; i++)
            {
                aluno_imprimir(torneio->competidores[i]->aluno);
            } 
            printf("\n--------------------------------------------------------------------------------------");*/
            temp = torneio_preencher_resultado(torneio_resultado, torneio, quant_vencedores);
        }

        torneio_imprimir_resultado(torneio_resultado, diario_get_nAlunos(diario));
        
        for (int i = 0; i < diario_get_nAlunos(diario); i++)
        {  
            diario_alterar_aluno(diario, torneio_resultado->competidores[i]->aluno, i);
            //aluno_imprimir(torneio_resultado->competidores[i]->aluno);
        }
        return TRUE;
    }
    return FALSE;
}

static boolean torneio_primeira_ordenacao(TORNEIO *torneio, int p_folhas, int t_arv, int n_notas)
{
    if (torneio != NULL)
    {   
        int aux =  t_arv-1;
        //O número total de comparaçoes na primeira ordenação é igual ao número de nos divido por 2 menos a raiz
        for (int i = 0; i < ((t_arv/2)-1); i++)
        {
            torneio_comparar_competidores(torneio, aux);
            aux-=2;
        }
    return TRUE;
    }
    return FALSE;
}

static boolean torneio_n_ordenacoes(TORNEIO *torneio, int posicao_alterada, int profundidade)
{

    if (torneio != NULL)
    {   
        int aux = posicao_alterada;
 
       for (int i = 0; i < profundidade; i++)//a quantidade de alterações a arvore será igual a profundidade da arvore
       {
            if(aux%2==0){
                aux++;
            }
            torneio_comparar_competidores(torneio, aux);
            aux = (aux-1)/2;
       }
       return TRUE;
    }

    return FALSE;
}


static boolean torneio_comparar_competidores(TORNEIO *torneio, int aux){
    if (torneio != NULL)
    { 
        if(aluno_get_media(torneio->competidores[aux-1]->aluno) != aluno_get_media(torneio->competidores[aux]->aluno)){
            //medias diferentes
            if(aluno_get_media(torneio->competidores[aux-1]->aluno) > aluno_get_media(torneio->competidores[aux]->aluno))
            {   
                torneio->competidores[aux/2] = torneio->competidores[aux-1];//filho direito: y = 2x, pai: y = x/2
            }else{
                torneio->competidores[(aux-1)/2] = torneio->competidores[aux];//filho esquerdo: y = 2x+1, pai: y = (x-1)/2
            }
        }else{
            //critério de desempate pelas notas
            if(aluno_get_media(torneio->competidores[aux-1]->aluno) == -1)
            {
                torneio->competidores[aux/2] = torneio->competidores[aux-1];//caso em que ambos tem media -1
            }else{
                for (int j = 0; j < aluno_get_nNotas(torneio->competidores[aux]->aluno); j++)
                {
                    if(aluno_get_nota(torneio->competidores[aux-1]->aluno, j) != aluno_get_nota(torneio->competidores[aux]->aluno,j)){
                        if(aluno_get_nota(torneio->competidores[aux-1]->aluno, j) > aluno_get_nota(torneio->competidores[aux]->aluno,j))
                        { 
                            //sprintf(torneio->competidores[aux-1]->criterio_desempate,"%s %d","desempate: nota", j+1);
                            if(torneio->competidores[aux-1]->criterio_desempate<j+1){
                                torneio->competidores[aux-1]->criterio_desempate = j+1;
                            }
                            torneio->competidores[aux/2] = torneio->competidores[aux-1];//filho direito: y = 2x, pai: y = x/2
                            break;
                        }else{
                            if(torneio->competidores[aux]->criterio_desempate<j+1){
                                torneio->competidores[aux]->criterio_desempate = j+1;
                            }
                            torneio->competidores[(aux-1)/2] = torneio->competidores[aux];//filho esquerdo: y = 2x+1, pai: y = (x-1)/2
                            break;
                        }
                    }
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

static int torneio_preencher_resultado(TORNEIO *torneio_resultado, TORNEIO *torneio,  int quant_vencedores){

    if (torneio != NULL)
    { 
        torneio_resultado->competidores[quant_vencedores] = torneio->competidores[1];
        int temp = torneio_resultado->competidores[quant_vencedores]->posicao_largada;
        torneio->competidores[temp] = competidor_criar(aluno_criar_null(), temp); 
        torneio_resultado->competidores[quant_vencedores]->posicao_largada = quant_vencedores+1;
        return temp;
    }

    return -1;
}

static void torneio_imprimir_resultado(TORNEIO *torneio_resultado, int n_alunos)
{
    printf("Maior media: %.3f ", aluno_get_media(torneio_resultado->competidores[0]->aluno));
    for (int i = 0; i < n_alunos-1; i++)
    {
        if(torneio_resultado->competidores[i]->criterio_desempate>0){
            printf("\n%d. %s - desempate: nota %d", i+1, aluno_get_nome(torneio_resultado->competidores[i]->aluno),torneio_resultado->competidores[i]->criterio_desempate);
        }else{
            printf("\n%d. %s - media", i+1, aluno_get_nome(torneio_resultado->competidores[i]->aluno));
        }
    }

    printf("\n%d. %s", n_alunos, aluno_get_nome(torneio_resultado->competidores[n_alunos-1]->aluno));
    
}