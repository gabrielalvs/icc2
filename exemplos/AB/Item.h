#ifndef TADGENERICO_ITEM_H
#define TADGENERICO_ITEM_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct item_st ITEM;

ITEM *item_criar_vazio();
ITEM *item_criar (int chave, const char *nome, const char *descricao, int ataque, int defesa);
ITEM *item_ler_std_in();
boolean item_apagar(ITEM **item);
void item_imprimir(const ITEM *item);
int item_get_chave(const ITEM *item);
boolean item_set_chave(ITEM *item, int chave);

#endif //TADGENERICO_ITEM_H
