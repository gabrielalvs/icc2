#include <stdio.h>

#include "aluno.h"
#include "diario.h"
#include "torneio.h"

int main() {
    int n_alunos;
    int n_notas;
    int nota;
    char nome[30];

    DIARIO *diario;
    scanf("%d %d", &n_alunos, &n_notas);

    diario = diario_criar(n_alunos,n_notas);

    ALUNO *aluno;
    for (int i = 0; i < diario_get_nAlunos(diario); i++)
    {
        scanf("%s\n", nome);
        aluno = aluno_criar(nome, diario_get_nNotas(diario));

        for (int j = 0; j < diario_get_nNotas(diario); j++)
        {
            scanf("%d/n", &nota);
            aluno_set_nota(aluno,nota);
        }

        aluno_media(aluno);
        diario_set_aluno(diario, aluno);
    }
    torneio_ordenar(diario);
    //diario_imprimir(diario);
    diario_apagar(&diario);
}