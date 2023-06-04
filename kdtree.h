#ifndef KDTREE_H
#define KDTREE_H

typedef struct _no
{
    void *item;
    struct _no *esq;
    struct _no *dir;
    struct _no *pai;
    int h; // altura do nó
} tno;

typedef struct _arv
{
    tno *raiz;
    int (*compara)(const void *a, const void *b, int altura);
} tarv;

tarv *criar_arvore(int (*compara)(const void *a, const void *b, int altura));
void inserir_no(tarv *arvore, void *item);
tno **encontrar_proximo(tarv *arv, void *item, int n);
void deletar_arvore(tarv *arvore);

#endif
