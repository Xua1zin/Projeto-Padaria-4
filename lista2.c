#include <stdio.h>
#include <stdlib.h>
#include "Produtos.h"

///Este arquivo serve para mexer na lista de produtos vendidos

void insere_inicio2(Lista *lista, No2* novo) ///função que adiciona o Node no começo da lista
{
    novo->anterior = NULL;
    novo->proximo = lista->inicio2;

    if (lista->inicio2 != NULL) ///caso a lista não esteja vazia
        lista->inicio2->anterior = novo;

    lista->inicio2 = novo;
}

void insere2(Lista *lista, No2* novo) ///função que adiciona o Node na lista
{
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio2 == NULL) ///caso a lista esteja vazia, chama a função que adiciona no inicio da lista
        insere_inicio2(lista, novo);

    else
    {
        No2* ptr = lista->inicio2; ///declaração de um ponteiro que percorrerá a lista

        if(ptr->vendido->subtotal > novo->vendido->subtotal) ///caso o subtotal da compra nova seja menor que a primeira da lista, ele adiciona antes do primeiro
            insere_inicio2(lista, novo);

        else
        {
            while (ptr->proximo != NULL && novo->vendido->subtotal > ptr->proximo->vendido->subtotal) ///percorre a lista até achar uma compra que o subtotal seja maior que o que está sendo inserido agora
                ptr = ptr->proximo;

            novo->proximo = ptr->proximo;

            if(ptr->proximo != NULL) ///caso não seja o último, o anterior da próxima compra é apontado para a nova compra
                ptr->proximo->anterior = novo;

            novo->anterior = ptr;
            ptr->proximo = novo;
        }
    }
}

void imprime2(Lista *lista) ///função que vai imprimir a lista para a nota fiscal
{
    int i = 1;
    No2* ptr = lista->inicio2;

    if(ptr == NULL) ///caso a lista estiver vazia
        puts("Não há produtos na lista.");

    else ///diferente da outra lista, essa não tem um produto específico para procurar, sempre vai imprimir todas as compras, pois ela serve para a nota fiscal
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
