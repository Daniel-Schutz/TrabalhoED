#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kdtree.h"

int main()
{
    NoKD *raiz = NULL;

    Ponto *ponto1 = (Ponto *)malloc(sizeof(Ponto));
    ponto1->x = 2.0;
    ponto1->y = 3.0;

    int *valor1 = (int *)malloc(sizeof(int));
    *valor1 = 10;

    Ponto *ponto2 = (Ponto *)malloc(sizeof(Ponto));
    ponto2->x = 5.0;
    ponto2->y = 4.0;

    char *valor2 = (char *)malloc(sizeof(char));
    *valor2 = 'A';

    Ponto *ponto3 = (Ponto *)malloc(sizeof(Ponto));
    ponto3->x = 9.0;
    ponto3->y = 6.0;

    Ponto *ponto4 = (Ponto *)malloc(sizeof(Ponto));
    ponto4->x = 4.0;
    ponto4->y = 7.0;

    Ponto *ponto5 = (Ponto *)malloc(sizeof(Ponto));
    ponto5->x = 8.0;
    ponto5->y = 1.0;

    inserirNo(&raiz, ponto1, valor1, 0);
    inserirNo(&raiz, ponto2, valor2, 0);
    inserirNo(&raiz, ponto3, "", 0);
    inserirNo(&raiz, ponto4, "", 0);
    inserirNo(&raiz, ponto5, "", 0);

    int k = 3;
    double distancias[3] = {INFINITY, INFINITY, INFINITY};
    Ponto vizinhos[3] = {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
    void *data[3] = {NULL, NULL, NULL};

    Ponto pontoBusca = {5.0, 4.0};

    encontrarVizinhos(raiz, pontoBusca, k, distancias, vizinhos, data);

    printf("Vizinhos mais próximos:\n");
    for (int i = 0; i < k; i++)
    {
        printf("(%.2f, %.2f) - Data: %d\n", vizinhos[i].x, vizinhos[i].y, *((int *)data[i]));
    }

    destruirArvore(raiz);

    assert(vizinhos[0].x == 2.0 && vizinhos[0].y == 3.0);
    assert(vizinhos[1].x == 9.0 && vizinhos[1].y == 6.0);
    assert(vizinhos[2].x == 4.0 && vizinhos[2].y == 7.0);

    printf("Passou em todos os testes!");

    return 0;
}
