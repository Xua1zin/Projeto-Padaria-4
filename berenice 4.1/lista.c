#include <stdio.h>
#include <stdlib.h>
#include "Produtos.h"

///Este arquivo serve para mexer na lista de produtos principal, estoque, etc.

void insere_inicio(Lista *lista, No* novo) ///função que adiciona o Node no começo da lista
{
    novo->anterior = NULL;
    novo->proximo = lista->inicio;

    if (lista->inicio != NULL) ///caso a lista não esteja vazia
        lista->inicio->anterior = novo;

    lista->inicio = novo;
}

void insere(Lista *lista, No* novo) ///função que adiciona o Node na lista
{
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->inicio == NULL) ///caso a lista esteja vazia, chama a função que adiciona no inicio da lista
        insere_inicio(lista, novo);

    else
    {
        No* ptr = lista->inicio; ///declaração de um ponteiro que percorrerá a lista

        if(novo->produto->codigo < ptr->produto->codigo) ///caso o código do produto novo seja menor que o primeiro da lista, ele adiciona antes do primeiro
            insere_inicio(lista, novo);

        else
        {
            while (ptr->proximo != NULL && novo->produto->codigo > ptr->proximo->produto->codigo) ///percorre a lista até achar um produto que o código seja maior que o que está sendo inserido agora
                ptr = ptr->proximo;

            novo->proximo = ptr->proximo;

            if(ptr->proximo != NULL) ///caso não seja o último, o anterior do próximo produto é apontado para o novo produto
                ptr->proximo->anterior = novo;

            novo->anterior = ptr;
            ptr->proximo = novo;
        }
    }
}

void remover(Lista *lista, No *ptr) ///função que remove o Node da lista
{
    if(ptr->anterior == NULL) ///caso seja o primeiro produto, o segundo vira o primeiro
        lista->inicio = ptr->proximo;

    else ///senão o próximo do anterior aponta para o próximo
        ptr->anterior->proximo = ptr->proximo;

    if(ptr->proximo != NULL) ///se não for o último, o anterior do próximo aponta para o anterior
        ptr->proximo->anterior = ptr->anterior;
}

void imprime(Lista *lista, unsigned long int codigo) ///função que vai imprimir a lista
{
    No* ptr = lista->inicio; ///ponteiro que percorre a lista

    if(ptr == NULL) ///caso a lista estiver vazia
        puts("Não há produtos na lista.");

    else
    {
        if (codigo == -1) ///como o código não pode ser cadastrado como -1, sempre que for, ele imprime a lista inteira
        {
            puts("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE");
            while (ptr != NULL)
            {
                printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", ptr->produto->codigo, ptr->produto->nome, ptr->produto->valor_unit, ptr->produto->quant_estoque);

                ptr = ptr->proximo;
            }
        }
        else ///caso seja um código específico, ele imprime somente o produto desse determinado código
        {
            puts("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE");
            while (ptr != NULL) ///ele percorre a lista inteira até encontrar o código, quando encontra, retorna
            {
                if (ptr->produto->codigo == codigo)
                {
                    printf("\t%-10lu     %-25s     %4.2f\t    %3d\n", ptr->produto->codigo, ptr->produto->nome, ptr->produto->valor_unit, ptr->produto->quant_estoque);
                    return;
                }


                ptr = ptr->proximo;
            }
                if(ptr == NULL) ///caso não encontre o código
                    printf("Código %lu não encontrado\n", codigo);
        }
    }
}
