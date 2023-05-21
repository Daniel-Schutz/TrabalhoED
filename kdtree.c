#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kdtree.h"

/* Funções principais:
   - Inserção: inserirNo
   - Busca: encontrarVizinhos
   - Destruição: destruirArvore
*/

// função auxiliar para a função encontrarVizinhos
double calcularDistancia(Ponto *ponto1, Ponto *ponto2)
{
    double difX = ponto1->x - ponto2->x;
    double difY = ponto1->y - ponto2->y;
    return sqrt(difX * difX + difY * difY);
}

// função auxiliar para a função inserirNo
NoKD *criarNo(Ponto *ponto, void *data)
{
    NoKD *no = (NoKD *)malloc(sizeof(NoKD));
    no->ponto = ponto;
    no->data = data;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

void inserirNo(NoKD **raiz, Ponto *ponto, void *data, int nivel)
{
    if (*raiz == NULL)
    {
        *raiz = criarNo(ponto, data);
    }
    else
    {
        int dimensaoAtual = nivel % 2;
        if (ponto->x < (*raiz)->ponto->x)
        {
            inserirNo(&(*raiz)->esquerda, ponto, data, nivel + 1);
        }
        else
        {
            inserirNo(&(*raiz)->direita, ponto, data, nivel + 1);
        }
    }
}

void encontrarVizinhos(NoKD *raiz, Ponto ponto, int k, double *distancias, Ponto *vizinhos, void **data)
{
    if (raiz == NULL)
    {
        return;
    }

    double distancia = calcularDistancia(&ponto, raiz->ponto);

    int posicaoInsercao = -1;
    for (int i = 0; i < k; i++)
    {
        if (vizinhos[i].x == 0.0 && vizinhos[i].y == 0.0)
        {
            posicaoInsercao = i;
            break;
        }
    }

    if (posicaoInsercao != -1)
    {
        // Verificar se o ponto é idêntico ao ponto de busca
        if (calcularDistancia(&ponto, raiz->ponto) != 0.0)
        {
            vizinhos[posicaoInsercao] = *raiz->ponto;
            distancias[posicaoInsercao] = distancia;
            data[posicaoInsercao] = raiz->data;
        }
    }
    else
    {
        int indiceVizinhoMaisDistante = 0;
        double distanciaVizinhoMaisDistante = distancias[0];

        for (int i = 1; i < k; i++)
        {
            if (distancias[i] > distanciaVizinhoMaisDistante)
            {
                distanciaVizinhoMaisDistante = distancias[i];
                indiceVizinhoMaisDistante = i;
            }
        }

        if (distancia < distanciaVizinhoMaisDistante && calcularDistancia(&ponto, raiz->ponto) != 0.0)
        {
            vizinhos[indiceVizinhoMaisDistante] = *raiz->ponto;
            distancias[indiceVizinhoMaisDistante] = distancia;
            data[indiceVizinhoMaisDistante] = raiz->data;
        }
    }

    int dimensaoAtual = raiz->ponto->x < ponto.x ? 0 : 1;

    if (dimensaoAtual == 0)
    {
        encontrarVizinhos(raiz->esquerda, ponto, k, distancias, vizinhos, data);
        if (fabs(raiz->ponto->x - ponto.x) < distancias[0])
        {
            encontrarVizinhos(raiz->direita, ponto, k, distancias, vizinhos, data);
        }
    }
    else
    {
        encontrarVizinhos(raiz->direita, ponto, k, distancias, vizinhos, data);
        if (fabs(raiz->ponto->x - ponto.x) < distancias[0])
        {
            encontrarVizinhos(raiz->esquerda, ponto, k, distancias, vizinhos, data);
        }
    }
}

void destruirArvore(NoKD *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    destruirArvore(raiz->esquerda);
    destruirArvore(raiz->direita);
    free(raiz->ponto);
    free(raiz);

    raiz->esquerda = NULL; // Adição da atribuição NULL aos ponteiros
    raiz->direita = NULL;  // esquerda e direita após a liberação da memória
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
} Ponto;

typedef struct NoKD
{
    void *ponto;
    struct NoKD *esquerda;
    struct NoKD *direita;
} NoKD;

double calcularDistancia(Ponto *ponto1, Ponto *ponto2)
{
    double difX = ponto1->x - ponto2->x;
    double difY = ponto1->y - ponto2->y;
    return sqrt(difX * difX + difY * difY);
}

NoKD *criarNo(void *ponto)
{
    NoKD *no = (NoKD *)malloc(sizeof(NoKD));
    no->ponto = ponto;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

void inserirNo(NoKD **raiz, void *ponto, int nivel)
{
    if (*raiz == NULL)
    {
        *raiz = criarNo(ponto);
    }
    else
    {
        int dimensaoAtual = nivel % 2;
        if (((Ponto *)ponto)->x < ((Ponto *)(*raiz)->ponto)->x)
        {
            inserirNo(&(*raiz)->esquerda, ponto, nivel + 1);
        }
        else
        {
            inserirNo(&(*raiz)->direita, ponto, nivel + 1);
        }
    }
}

void encontrarVizinhos(NoKD *raiz, Ponto ponto, int k, double *distancias, Ponto *vizinhos)
{
    if (raiz == NULL)
    {
        return;
    }

    double distancia = calcularDistancia(&ponto, (Ponto *)raiz->ponto);

    int posicaoInsercao = -1;
    for (int i = 0; i < k; i++)
    {
        if (vizinhos[i].x == 0.0 && vizinhos[i].y == 0.0)
        {
            posicaoInsercao = i;
            break;
        }
    }

    if (posicaoInsercao != -1)
    {
        vizinhos[posicaoInsercao] = *(Ponto *)raiz->ponto;
        distancias[posicaoInsercao] = distancia;
    }
    else
    {
        int indiceVizinhoMaisDistante = 0;
        double distanciaVizinhoMaisDistante = distancias[0];

        for (int i = 1; i < k; i++)
        {
            if (distancias[i] > distanciaVizinhoMaisDistante)
            {
                distanciaVizinhoMaisDistante = distancias[i];
                indiceVizinhoMaisDistante = i;
            }
        }

        if (distancia < distanciaVizinhoMaisDistante)
        {
            vizinhos[indiceVizinhoMaisDistante] = *(Ponto *)raiz->ponto;
            distancias[indiceVizinhoMaisDistante] = distancia;
        }
    }

    int dimensaoAtual = ((Ponto *)raiz->ponto)->x < ponto.x ? 0 : 1;

    if (dimensaoAtual == 0)
    {
        encontrarVizinhos(raiz->esquerda, ponto, k, distancias, vizinhos);
        if (fabs(((Ponto *)raiz->ponto)->x - ponto.x) < distancias[0])
        {
            encontrarVizinhos(raiz->direita, ponto, k, distancias, vizinhos);
        }
    }
    else
    {
        encontrarVizinhos(raiz->direita, ponto, k, distancias, vizinhos);
        if (fabs(((Ponto *)raiz->ponto)->x - ponto.x) < distancias[0])
        {
            encontrarVizinhos(raiz->esquerda, ponto, k, distancias, vizinhos);
        }
    }
}

void destruirArvore(NoKD *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    destruirArvore(raiz->esquerda);
    destruirArvore(raiz->direita);

    free(raiz->ponto);
    free(raiz);
}*/
