#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kdtree.h"

tarv *criar_arvore(int (*compara)(const void *a, const void *b, int altura))
{
    tarv *nova_arvore = (tarv *)malloc(sizeof(tarv));
    if (nova_arvore)
    {
        nova_arvore->raiz = NULL;
        nova_arvore->compara = compara;
    }
    return nova_arvore;
}

tno *criar_no(void *item)
{
    tno *novo_no = (tno *)malloc(sizeof(tno));
    if (novo_no)
    {
        novo_no->item = item;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->pai = NULL;
        novo_no->h = 0; // altura do nó inicializada como 0
    }
    return novo_no;
}

void inserir_no(tarv *arvore, void *item)
{
    if (arvore == NULL || item == NULL)
        return;

    tno *novo_no = criar_no(item);
    if (novo_no == NULL)
        return;

    if (arvore->raiz == NULL)
    {
        arvore->raiz = novo_no;
    }
    else
    {
        tno *atual = arvore->raiz;
        tno *pai;

        while (1)
        {
            pai = atual;

            if (arvore->compara(item, atual->item, atual->h) < 0)
            {
                atual = atual->esq;
                if (atual == NULL)
                {
                    pai->esq = novo_no;
                    novo_no->pai = pai;
                    novo_no->h = pai->h + 1; // atualiza a altura do novo nó
                    break;
                }
            }
            else
            {
                atual = atual->dir;
                if (atual == NULL)
                {
                    pai->dir = novo_no;
                    novo_no->pai = pai;
                    novo_no->h = pai->h + 1; // atualiza a altura do novo nó
                    break;
                }
            }
        }
    }
}

tno *buscar_no(tarv *arvore, void *item)
{
    if (arvore == NULL || arvore->raiz == NULL || item == NULL)
        return NULL;

    tno *atual = arvore->raiz;
    tno *ultimoVerificado = NULL;

    while (atual != NULL)
    {
        if (arvore->compara(item, atual->item, atual->h) == 0)
        {
            return atual;
        }
        else if (arvore->compara(item, atual->item, atual->h) < 0)
        {
            ultimoVerificado = atual;
            atual = atual->esq;
        }
        else
        {
            ultimoVerificado = atual;
            atual = atual->dir;
        }
    }

    return ultimoVerificado;
}

void liberar_arvore(tno *no)
{
    if (no == NULL)
    {
        return;
    }

    liberar_arvore(no->esq); // liberar o filho esquerdo
    liberar_arvore(no->dir); // liberar o filho direito

    free(no); // liberar o nó atual
}

void deletar_arvore(tarv *arvore)
{
    if (arvore == NULL)
    {
        return;
    }

    liberar_arvore(arvore->raiz);
    arvore->raiz = NULL;

    free(arvore);
}

tno *sucessor_no(tno *no)
{
    if (no->dir != NULL)
    {
        no = no->dir;
        while (no->esq != NULL)
            no = no->esq;
        return no;
    }

    tno *pai = no->pai;
    while (pai != NULL && no == pai->dir)
    {
        no = pai;
        pai = pai->pai;
    }

    return pai;
}

tno *predecessor_no(tno *no)
{
    if (no->esq != NULL)
    {
        no = no->esq;
        while (no->dir != NULL)
            no = no->dir;
        return no;
    }

    tno *pai = no->pai;
    while (pai != NULL && no == pai->esq)
    {
        no = pai;
        pai = pai->pai;
    }

    return pai;
}

tno **encontrar_proximo(tarv *arv, void *item, int n)
{
    tno *noAlvo = buscar_no(arv, item);

    if (noAlvo == NULL)
    {
        printf("No não encontrado na árvore.\n");
        return NULL;
    }

    tno **vizinhos = (tno **)malloc((2 * n + 1) * sizeof(tno *));
    tno *atual = noAlvo;
    int count = 0;

    vizinhos[count] = atual;
    count++;

    while (count < (2 * n + 1) && atual != NULL)
    {
        tno *predecessor = predecessor_no(atual);
        if (predecessor != NULL)
        {
            vizinhos[count] = predecessor;
            count++;
        }

        tno *sucessor = sucessor_no(atual);
        if (sucessor != NULL)
        {
            vizinhos[count] = sucessor;
            count++;
        }

        atual = atual->pai;
    }

    return vizinhos;
}

