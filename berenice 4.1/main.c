#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Produtos.h"

///Arquivo da main, ela est� servindo principalmente para o menu principal do programa

int main()
{
    setlocale(LC_CTYPE, "Portuguese"); ///define os acentos em portugu�s

    int opcao = 0, counter = 0;
    Lista *lista = (Lista*) malloc(sizeof(Lista)); ///aloca dinamicamente o inicio da lista
    lista->inicio = NULL; ///define o inicio da lista 1 como vazia
    lista->inicio2 = NULL; ///define o inicio da lista 2 como vazia
    do
    {
        system(CLEAR);
        printf("     C�DIGO  |   OP��O\n\t1\tProdutos\n\t2\tVendas\n\t3\tSair\n\nDigite um c�digo: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 1)
        {
            system(CLEAR);
            leitura_arquivo(lista);
            funcao_produto(lista);
        }

        else if(opcao == 2)
        {
            system(CLEAR);
            leitura_arquivo(lista);
            vendas(lista);
        }

        else if(opcao == 3) ///sempre que seleciona sair, ele limpa todas as listas e da free nos espa�os de mem�ria
        {
            counter = 1;
            system(CLEAR);
            printf("Obrigado por usar nosso programa!\n");
            No *ptr = lista->inicio;
            No2 *ptr2 = lista->inicio2;
            No *apagar;
            No2 *apagar2;
            while(ptr != NULL)
            {
                apagar = ptr;
                ptr = ptr->proximo;
                free(apagar->produto);
                free(apagar);
            }
            while(ptr2 != NULL)
            {
                apagar2 = ptr2;
                ptr2 = ptr2->proximo;
                free(apagar2->vendido);
                free(apagar2);
            }
            free(lista);
        }

        else
            printf("\nC�digo inv�lido\n\nDigite um c�digo v�lido: ");
    }
    while(counter == 0);

    return 0;
}
