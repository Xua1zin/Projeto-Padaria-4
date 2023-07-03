#include <stdio.h>
#include <stdlib.h>
#include "Produtos.h"

///Este arquivo serve para mexer na lista de produtos principal, estoque, etc.

void insere_inicio(Lista *lista, No* novo) ///fun��o que adiciona o Node no come�o da lista
{
    novo->anterior = NULL;
    novo->proximo = lista->inicio;

    if (lista->inicio != NULL) ///caso a lista n�o esteja vazia
        lista->inicio->anterior = novo;

    lista->inicio = novo;
}

void insere(Lista *lista, No* novo) ///fun��o que adiciona o Node na lista
{
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio == NULL) ///caso a lista esteja vazia, chama a fun��o que adiciona no inicio da lista
        insere_inicio(lista, novo);

    else
    {
        No* ptr = lista->inicio; ///declara��o de um ponteiro que percorrer� a lista

        if(novo->produto->codigo < ptr->produto->codigo) ///caso o c�digo do produto novo seja menor que o primeiro da lista, ele adiciona antes do primeiro
            insere_inicio(lista, novo);

        else
        {
            while (ptr->proximo != NULL && novo->produto->codigo > ptr->proximo->produto->codigo) ///percorre a lista at� achar um produto que o c�digo seja maior que o que est� sendo inserido agora
                ptr = ptr->proximo;

            novo->proximo = ptr->proximo;

            if(ptr->proximo != NULL) ///caso n�o seja o �ltimo, o anterior do pr�ximo produto � apontado para o novo produto
                ptr->proximo->anterior = novo;

            novo->anterior = ptr;
            ptr->proximo = novo;
        }
    }
}

void remover(Lista *lista, No *ptr) ///fun��o que remove o Node da lista
{
    if(ptr->anterior == NULL) ///caso seja o primeiro produto, o segundo vira o primeiro
        lista->inicio = ptr->proximo;

    else ///sen�o o pr�ximo do anterior aponta para o pr�ximo
        ptr->anterior->proximo = ptr->proximo;

    if(ptr->proximo != NULL) ///se n�o for o �ltimo, o anterior do pr�ximo aponta para o anterior
        ptr->proximo->anterior = ptr->anterior;
}

void imprime(Lista *lista, unsigned long int codigo) ///fun��o que vai imprimir a lista
{
    No* ptr = lista->inicio; ///ponteiro que percorre a lista

    if(ptr == NULL) ///caso a lista estiver vazia
        puts("N�o h� produtos na lista.");

    else
    {
        if (codigo == -1) ///como o c�digo n�o pode ser cadastrado como -1, sempre que for, ele imprime a lista inteira
        {
            puts("        C�DIGO       |           NOME           |    VALOR    |    ESTOQUE");
            while (ptr != NULL)
            {
                printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", ptr->produto->codigo, ptr->produto->nome, ptr->produto->valor_unit, ptr->produto->quant_estoque);

                ptr = ptr->proximo;
            }
        }
        else ///caso seja um c�digo espec�fico, ele imprime somente o produto desse determinado c�digo
        {
            puts("        C�DIGO       |           NOME           |    VALOR    |    ESTOQUE");
            while (ptr != NULL) ///ele percorre a lista inteira at� encontrar o c�digo, quando encontra, retorna
            {
                if (ptr->produto->codigo == codigo)
                {
                    printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", ptr->produto->codigo, ptr->produto->nome, ptr->produto->valor_unit, ptr->produto->quant_estoque);
                    return;
                }


                ptr = ptr->proximo;
            }
                if(ptr == NULL) ///caso n�o encontre o c�digo
                    printf("C�digo %lu n�o encontrado\n", codigo);
        }
    }
}
