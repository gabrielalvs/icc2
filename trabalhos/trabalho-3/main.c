#include <stdio.h>
#include "aluno.h"
#include "lista.h"
#include "tabelahash.h"

int main() {
    TABELAHASH *tabelahash = tabelahash_criar(256);
    ALUNO *aluno = NULL;
    int control;
    char senha[30];
    char nusp[30];
    float n1;
    float n2;
    float n3;
    float n4;

    scanf("%d", &control);

    for (int i = 0; i < control; i++)
    {
        scanf("%s %s %f %f %f %f", nusp, senha, &n1, &n2, &n3, &n4);

        aluno = aluno_criar(nusp, hash(senha));
        aluno_set_nota(aluno, n1);
        aluno_set_nota(aluno, n2);
        aluno_set_nota(aluno, n3);
        aluno_set_nota(aluno, n4);
        tabelahash_set_aluno(tabelahash, aluno);
    }
    
    scanf("%d", &control);

    for (int i = 0; i < control; i++)
    {
        scanf("%s %s", nusp, senha);

        switch (tabelahash_logar(tabelahash, nusp, hash(senha))) {
            case 0:
                aluno_imprimir_notas(tabelahash_get_aluno(tabelahash, nusp));
                break;
            case 1:
                printf("Senha incorreta para o NUSP digitado \n");
                break;
            case 2:
                printf("NUSP invalido \n");
                break;
            default:
                printf("ERRO \n");
            break;
        }
    }

    tabelahash_apagar(&tabelahash);
}