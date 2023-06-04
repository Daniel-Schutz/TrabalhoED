#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
        restaurante *r = malloc(sizeof(restaurante));

        sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%d,%[^,],%[^\n]",
               &r->linha, r->address, r->categories, r->city, r->country, &r->latitude, &r->longitude, r->name, &r->postalCode, r->province, r->websites);

        inserir_no(arvore, r);
    }

    fclose(arquivo);
    int quantidade_proximos = 5;

    // Caso de teste 1:
    restaurante restaurante_busca1;
    restaurante_busca1.latitude = 33.475292;
    restaurante_busca1.longitude = -81.995946;
    /*Esperado encontrar o restaurante:
    22,1720 Walton Way,Fast Food Restaurants,Augusta,US,33.475292,-81.995946,Checkers,30904,GA,"https://locations.checkers.com/ga/augusta/1720-walton-way,https://www.checkers.com"
    Logo, restaurante_test1->postalCode == 30904*/
    tno **nos_proximos1 = encontrar_proximo(arvore, &restaurante_busca1, quantidade_proximos);
    restaurante *restaurante_test1 = (restaurante *)nos_proximos1[0]->item;

    // Caso de teste 2, usando um valor que não vai cair exatamente num restaurante:
    restaurante restaurante_busca2;
    restaurante_busca2.latitude = 33.475592;
    restaurante_busca2.longitude = -81.995646;
    /*Esperado encontrar o restaurante:
    22,1720 Walton Way,Fast Food Restaurants,Augusta,US,33.475292,-81.995946,Checkers,30904,GA,"https://locations.checkers.com/ga/augusta/1720-walton-way,https://www.checkers.com"
    Logo, restaurante_test2->postalCode == 30904*/
    tno **nos_proximos2 = encontrar_proximo(arvore, &restaurante_busca2, quantidade_proximos);
    restaurante *restaurante_test2 = (restaurante *)nos_proximos2[0]->item;

    // Caso de teste 3:
    restaurante restaurante_busca3;
    restaurante_busca3.latitude = 33.205722;
    restaurante_busca3.longitude = -117.288645;
    /*Esperado encontrar o restaurante:
   7,4111 Oceanside Blvd,Fast Food,Oceanside,US,33.205722,-117.288645,Chipotle Mexican Grill,92056,CA,"http://www.chipotle.com,http://www.lasalsa.com"
    Logo, restaurante_test3->postalCode == 92056*/
    tno **nos_proximos3 = encontrar_proximo(arvore, &restaurante_busca3, quantidade_proximos);
    restaurante *restaurante_test3 = (restaurante *)nos_proximos3[0]->item;

    // Caso de teste 4:
    restaurante restaurante_busca4;
    restaurante_busca4.latitude = 32.805002;
    restaurante_busca4.longitude = -96.81357;
    /*Esperado encontrar o restaurante:
    9982,2529 Oak Lawn Ave,Fast Food Restaurants,Dallas,US,32.805002,-96.81357,7-Eleven,75219,TX,"https://www.7-eleven.com/locations/tx/dallas/2529-oak-lawn-ave-12200,http://www.7-eleven.com,http://www.7-eleven.com/?yext=12200"
    Logo, restaurante_test4->postalCode == 75219*/
    tno **nos_proximos4 = encontrar_proximo(arvore, &restaurante_busca4, quantidade_proximos);
    restaurante *restaurante_test4 = (restaurante *)nos_proximos4[0]->item;

    // Caso de teste 5, usando um valor que não vai cair exatamente num restaurante::
    restaurante restaurante_busca5;
    restaurante_busca5.latitude = 42.20835;
    restaurante_busca5.longitude = -83.15068;
    /*Esperado encontrar o restaurante:
    9949,3421 Biddle Ave,Fast Food Restaurant,Wyandotte,US,42.19835,-83.14968,McDonald's,48192,MI,"http://mcdonalds.com,http://www.mcdonalds.com/?cid=RF:YXT_FM:TP::Yext:Referral,http://www.mcdonalds.com"
    Logo, restaurante_test5->postalCode == 48192*/
    tno **nos_proximos5 = encontrar_proximo(arvore, &restaurante_busca5, quantidade_proximos);
    restaurante *restaurante_test5 = (restaurante *)nos_proximos5[0]->item;

    assert(restaurante_test1->postalCode == 30904);
    assert(restaurante_test2->postalCode == 30904);
    assert(restaurante_test3->postalCode == 92056);
    assert(restaurante_test4->postalCode == 75219);
    assert(restaurante_test5->postalCode == 48192);

    printf("Passou em todos os testes!");
    deletar_arvore(arvore);

    return 0; // Sair do programa com sucesso
}
