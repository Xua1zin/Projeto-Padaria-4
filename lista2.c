#include <stdio.h>
#include <stdlib.h>
#include "Produtos.h"

///Este arquivo serve para mexer na lista de produtos vendidos

void insere_inicio2(Lista *lista, No2* novo) ///fun��o que adiciona o Node no come�o da lista
{
    novo->anterior = NULL;
    novo->proximo = lista->inicio2;

    if (lista->inicio2 != NULL) ///caso a lista n�o esteja vazia
        lista->inicio2->anterior = novo;

    lista->inicio2 = novo;
}

void insere2(Lista *lista, No2* novo) ///fun��o que adiciona o Node na lista
{
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio2 == NULL) ///caso a lista esteja vazia, chama a fun��o que adiciona no inicio da lista
        insere_inicio2(lista, novo);

    else
    {
        No2* ptr = lista->inicio2; ///declara��o de um ponteiro que percorrer� a lista

        if(ptr->vendido->subtotal > novo->vendido->subtotal) ///caso o subtotal da compra nova seja menor que a primeira da lista, ele adiciona antes do primeiro
            insere_inicio2(lista, novo);

        else
        {
            while (ptr->proximo != NULL && novo->vendido->subtotal > ptr->proximo->vendido->subtotal) ///percorre a lista at� achar uma compra que o subtotal seja maior que o que est� sendo inserido agora
                ptr = ptr->proximo;

            novo->proximo = ptr->proximo;

            if(ptr->proximo != NULL) ///caso n�o seja o �ltimo, o anterior da pr�xima compra � apontado para a nova compra
                ptr->proximo->anterior = novo;

            novo->anterior = ptr;
            ptr->proximo = novo;
        }
    }
}

void imprime2(Lista *lista) ///fun��o que vai imprimir a lista para a nota fiscal
{
    int i = 1;
    No2* ptr = lista->inicio2;

    if(ptr == NULL) ///caso a lista estiver vazia
        puts("N�o h� produtos na lista.");

    else ///diferente da outra lista, essa n�o tem um produto espec�fico para procurar, sempre vai imprimir todas as compras, pois ela serve para a nota fiscal
    {
        puts("   ITEM   |           NOME           |    VALOR    |    QUANTIDADE    |   SUBTOTAL");
        while (ptr != NULL)
        {
            printf("    %2d\t    %-25s    R$%4.2f\t           %2d\t           R$%4.2f\n", i, ptr->vendido->nome, ptr->vendido->valor_unit, ptr->vendido->quant_vendida, ptr->vendido->subtotal);

            ptr = ptr->proximo;
            i += 1;
        }
    }
}
