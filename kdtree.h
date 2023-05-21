#ifndef KDTREE_H
#define KDTREE_H

typedef struct
{
    double x;
    double y;
} Ponto;

typedef struct NoKD
{
    Ponto *ponto;
    void *data;
    struct NoKD *esquerda;
    struct NoKD *direita;
} NoKD;

void inserirNo(NoKD **raiz, Ponto *ponto, void *data, int nivel);
void encontrarVizinhos(NoKD *raiz, Ponto ponto, int k, double *distancias, Ponto *vizinhos, void **data);
void destruirArvore(NoKD *raiz);

#endif
