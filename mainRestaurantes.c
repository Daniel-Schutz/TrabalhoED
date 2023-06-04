#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"

typedef struct _restaurantes
{
    int linha;
    char address[100];
    char categories[100];
    char city[100];
    char country[100];
    float latitude;
    float longitude;
    char name[100];
    int postalCode;
    char province[3];
    char websites[800];
} restaurante;

int compara_restaurantes(const void *a, const void *b, int altura)
{
    restaurante *restaurante_a = (restaurante *)a;
    restaurante *restaurante_b = (restaurante *)b;

    if (altura % 2 == 0)
    {
        if (restaurante_a->latitude < restaurante_b->latitude)
            return -1;
        else if (restaurante_a->latitude > restaurante_b->latitude)
            return 1;
        else
            return 0;
    }
    else
    {
        if (restaurante_a->longitude < restaurante_b->longitude)
            return -1;
        else if (restaurante_a->longitude > restaurante_b->longitude)
            return 1;
        else
            return 0;
    }
}

void imprimir_arvore_restaurante(tno *no)
{
    if (no != NULL)
    {
        restaurante *restaurante_atual = (restaurante *)no->item;
        printf("\n");
        printf("restaurante: %s\n", restaurante_atual->name);
        printf("Endereco: %s\n", restaurante_atual->address);
        printf("Categoria: %s\n", restaurante_atual->categories);
        printf("Cidade: %s\n", restaurante_atual->city);
        printf("Pais: %s\n", restaurante_atual->country);
        printf("Latitude: %f\n", restaurante_atual->latitude);
        printf("Longitude: %f\n", restaurante_atual->longitude);
        printf("Codigo Postal: %d\n", restaurante_atual->postalCode);
        printf("Estado: %s\n", restaurante_atual->province);
        printf("Websites: %s\n", restaurante_atual->websites);
        printf("\n");

        imprimir_arvore_restaurante(no->esq);
        imprimir_arvore_restaurante(no->dir);
    }
}

void imprimir_nos(tno **nos, int quantidade)
{
    printf("\nRestaurantes mais proximos:");
    for (int i = 0; i < quantidade; i++)
    {
        if (nos[i] != NULL)
        {
            restaurante *restaurante_atual = (restaurante *)nos[i]->item;
            printf("Nome: %s\n", restaurante_atual->name);
            printf("Endereco: %s\n", restaurante_atual->address);
            printf("Categoria: %s\n", restaurante_atual->categories);
            printf("Cidade: %s\n", restaurante_atual->city);
            printf("Pais: %s\n", restaurante_atual->country);
            printf("Latitude: %f\n", restaurante_atual->latitude);
            printf("Longitude: %f\n", restaurante_atual->longitude);
            printf("Codigo Postal: %d\n", restaurante_atual->postalCode);
            printf("Estado: %s\n", restaurante_atual->province);
            printf("Websites: %s\n", restaurante_atual->websites);
            printf("\n");
        }
        else
        {
            printf("Restaurantes mais proximos ja encontrados.\n");
        }
    }
}

int main()
{
    tarv *arvore = criar_arvore(compara_restaurantes);
    FILE *arquivo = fopen("Fast_Food_Restaurants.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[900];
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        restaurante *restaurante_atual = malloc(sizeof(restaurante));

        sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%d,%[^,],%[^\n]",
               &restaurante_atual->linha, restaurante_atual->address, restaurante_atual->categories, restaurante_atual->city, restaurante_atual->country, &restaurante_atual->latitude, &restaurante_atual->longitude, restaurante_atual->name, &restaurante_atual->postalCode, restaurante_atual->province, restaurante_atual->websites);

        inserir_no(arvore, restaurante_atual);
    }

    fclose(arquivo);

    restaurante restaurante_busca;
    int quantidade_proximos = 5;
    int opcao;
    printf("Problema 2: retornar os fastfoods mais proximos. Digite sua opcao:\n");
    do
    {
        printf("1 - Buscar restaurante\n");
        printf("2 - Encerrar Programa\n");
        scanf("%d", &opcao);
        if (opcao < 1 || opcao > 2)
        {
            printf("\nEscreva um numero valido!\n");
        }
        if (opcao == 1)
        {
            printf("\nDigite a latitude que voce deseja pesquisar:");
            scanf("%f", &restaurante_busca.latitude);
            printf("\nDigite a longitude que voce deseja pesquisar:");
            scanf("%f", &restaurante_busca.longitude);
            tno **nos_proximos = encontrar_proximo(arvore, &restaurante_busca, quantidade_proximos);
            imprimir_nos(nos_proximos, quantidade_proximos);
        }

    } while (opcao != 2);

    deletar_arvore(arvore);

    return 0;
}
