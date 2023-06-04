#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// função para imprimir a arvore completa
void imprimir_arvore_cidade(tno *no)
{
    if (no != NULL)
    {
        cidade *cidade_atual = (cidade *)no->item;
        printf("\n");
        printf("Cidade: %s\n", cidade_atual->nome);
        printf("Codigo IBGE: %d\n", cidade_atual->codigo_ibge);
        printf("Latitude: %f\n", cidade_atual->latitude);
        printf("Longitude: %f\n", cidade_atual->longitude);
        printf("Capital: %d\n", cidade_atual->capital);
        printf("Codigo UF: %d\n", cidade_atual->codigo_uf);
        printf("Siafi ID: %d\n", cidade_atual->siafi_id);
        printf("DDD: %d\n", cidade_atual->ddd);
        printf("Fuso Horario: %s\n", cidade_atual->fuso_horario);
        printf("\n");

        imprimir_arvore_cidade(no->esq);
        imprimir_arvore_cidade(no->dir);
    }
}

void imprimir_nos(tno **nos, int quantidade)
{
    printf("\nCidade mais proxima:\n");
    for (int i = 0; i < quantidade; i++)
    {
        if (nos[i] != NULL)
        {
            cidade *cidade_atual = (cidade *)nos[i]->item;
            printf("Cidade: %s\n", cidade_atual->nome);
            printf("Codigo IBGE: %d\n", cidade_atual->codigo_ibge);
            printf("Latitude: %f\n", cidade_atual->latitude);
            printf("Longitude: %f\n", cidade_atual->longitude);
            printf("Capital: %d\n", cidade_atual->capital);
            printf("Codigo UF: %d\n", cidade_atual->codigo_uf);
            printf("Siafi ID: %d\n", cidade_atual->siafi_id);
            printf("DDD: %d\n", cidade_atual->ddd);
            printf("Fuso Horario: %s\n", cidade_atual->fuso_horario);
            printf("\n");
        }
        else
        {
            printf("Cidades mais proximas ja encontradas.\n");
        }
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
        cidade *cidade_atual = malloc(sizeof(cidade));

        fscanf(arquivo, "%d, %[^,], %f, %f, %d, %d, %d, %d, %[^,\n]", &cidade_atual->codigo_ibge, cidade_atual->nome, &cidade_atual->latitude, &cidade_atual->longitude, &cidade_atual->capital, &cidade_atual->codigo_uf, &cidade_atual->siafi_id, &cidade_atual->ddd, cidade_atual->fuso_horario);
        inserir_no(arvore, cidade_atual);
    }

    // Fechar o arquivo
    fclose(arquivo);

    cidade cidade_busca;
    int quantidade_proximos = 1;
    int opcao;
    printf("Problema 1: cidade mais proxima. Digite sua opcao:\n");
    do
    {
        printf("1 - Buscar municipio\n");
        printf("2 - Encerrar Programa\n");
        scanf("%d", &opcao);
        if (opcao < 1 || opcao > 2)
        {
            printf("\nEscreva um numero valido!\n");
        }
        if (opcao == 1)
        {
            printf("\nDigite a latitude que voce deseja pesquisar:");
            scanf("%f", &cidade_busca.latitude);
            printf("\nDigite a longitude que voce deseja pesquisar:");
            scanf("%f", &cidade_busca.longitude);
            tno **nos_proximos = encontrar_proximo(arvore, &cidade_busca, quantidade_proximos);
            imprimir_nos(nos_proximos, quantidade_proximos);
        }

    } while (opcao != 2);
    deletar_arvore(arvore);

    return 0;
}
