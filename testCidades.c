#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kdtree.h"

typedef struct _cidades
{
    int codigo_ibge;
    char nome[100];
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[100];
} cidade;

int compara_cidades(const void *a, const void *b, int altura)
{
    cidade *cidade_a = (cidade *)a;
    cidade *cidade_b = (cidade *)b;

    if (altura % 2 == 0)
    {
        if (cidade_a->latitude < cidade_b->latitude)
            return -1;
        else if (cidade_a->latitude > cidade_b->latitude)
            return 1;
        else
            return 0;
    }
    else
    {
        if (cidade_a->longitude < cidade_b->longitude)
            return -1;
        else if (cidade_a->longitude > cidade_b->longitude)
            return 1;
        else
            return 0;
    }
}

int main()
{
    tarv *arvore = criar_arvore(compara_cidades);
    FILE *arquivo;

    // Abrir o arquivo em modo de leitura
    arquivo = fopen("cidades.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    while (!feof(arquivo))
    {
        cidade *aux = malloc(sizeof(cidade));

        // fscanf(arq, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%[^,],%[^,],%[^,\n]", &i, aux.address, aux.categories, aux.city, aux.country, &aux.latitude, &aux.longitude, aux.name, aux.postalCode, aux.province, aux.websites);
        fscanf(arquivo, "%d, %[^,], %f, %f, %d, %d, %d, %d, %[^,\n]", &aux->codigo_ibge, aux->nome, &aux->latitude, &aux->longitude, &aux->capital, &aux->codigo_uf, &aux->siafi_id, &aux->ddd, aux->fuso_horario);
        inserir_no(arvore, aux);
    }

    // Fechar o arquivo
    fclose(arquivo);

    int quantidade_proximos = 1;

    // Caso de teste 1:
    cidade cidade_busca1;
    cidade_busca1.latitude = -4.95333;
    cidade_busca1.longitude = -48.3933;
    /*Esperado encontrar a cidade:
    1500131,Abel Figueiredo,-4.95333,-48.3933,0,15,0375,94,America/Sao_Paulo
    Logo, cidade_test1->codigo_ibge == 1500131*/
    tno **nos_proximos1 = encontrar_proximo(arvore, &cidade_busca1, quantidade_proximos);
    cidade *cidade_test1 = (cidade *)nos_proximos1[0]->item;

    // Caso de teste 2, usando um valor que não vai cair exatamente numa cidade:
    cidade cidade_busca2;
    cidade_busca2.latitude = -5.000;
    cidade_busca2.longitude = -48.3933;
    /*Esperado encontrar a cidade:
    1500131,Abel Figueiredo,-4.95333,-48.3933,0,15,0375,94,America/Sao_Paulo
    Logo, cidade_test2->codigo_ibge == 1500131*/
    tno **nos_proximos2 = encontrar_proximo(arvore, &cidade_busca2, quantidade_proximos);
    cidade *cidade_test2 = (cidade *)nos_proximos2[0]->item;

    // Caso de teste 3:
    cidade cidade_busca3;
    cidade_busca3.latitude = -29.748;
    cidade_busca3.longitude = -52.2748;
    /*Esperado encontrar a cidade:
    4314076,Passo do Sobrado,-29.748,-52.2748,0,43,5765,51,America/Sao_Paulo
    Logo, cidade_test3->codigo_ibge == 4314076*/
    tno **nos_proximos3 = encontrar_proximo(arvore, &cidade_busca3, quantidade_proximos);
    cidade *cidade_test3 = (cidade *)nos_proximos3[0]->item;

    // Caso de teste 4,usando um valor que não vai cair exatamente numa cidade::
    cidade cidade_busca4;
    cidade_busca4.latitude = -20.4586;
    cidade_busca4.longitude = -54.6395;
    /*Esperado encontrar a cidade:
    5002704,Campo Grande,-20.4486,-54.6295,1,50,9051,67,America/Porto_Velho
    Logo, cidade_test4->codigo_ibge == 5002704*/
    tno **nos_proximos4 = encontrar_proximo(arvore, &cidade_busca4, quantidade_proximos);
    cidade *cidade_test4 = (cidade *)nos_proximos4[0]->item;

    // Caso de teste 5:
    cidade cidade_busca5;
    cidade_busca5.latitude = -21.0737;
    cidade_busca5.longitude = -48.4126;
    /*Esperado encontrar a cidade:
    3553658,Taquaral,-21.0737,-48.4126,0,35,0824,16,America/Sao_Paulo
    Logo, cidade_test5->codigo_ibge == 3553658*/
    tno **nos_proximos5 = encontrar_proximo(arvore, &cidade_busca5, quantidade_proximos);
    cidade *cidade_test5 = (cidade *)nos_proximos5[0]->item;

    assert(cidade_test1->codigo_ibge == 1500131);
    assert(cidade_test2->codigo_ibge == 1500131);
    assert(cidade_test3->codigo_ibge == 4314076);
    assert(cidade_test4->codigo_ibge == 5002704);
    assert(cidade_test5->codigo_ibge == 3553658);

    printf("Passou em todos os testes!");
    deletar_arvore(arvore);

    return 0; // Sair do programa com sucesso
}
