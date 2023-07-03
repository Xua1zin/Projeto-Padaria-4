#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"

///Arquivo respons�vel pelas vendas

float realizar_vendas(Lista *lista) ///Fun��o de compra
{
    int quant_item = 0, counter = 0, repete = 0, menu;
    unsigned long int codigo;
    float valor_total = 0;
    No *ptr;
    No2 *novo;
    lista->inicio2 = NULL; ///Zera a lista de compras

    do
    {
        do
        {
            ptr = lista->inicio; ///define um ponteiro para percorrer a lista de produtos
            system(CLEAR);
            imprime(lista, -1);
            printf("\nDigite o c�digo do item escolhido: ");
            do
            {
                ptr = lista->inicio;
                scanf("%lu", &codigo);
                getchar();

                while(ptr != NULL)
                {
                    if(codigo == ptr->produto->codigo) ///verifica se o c�digo digitado existe, caso exista, sai do while
                    {
                        counter = 0;
                        break;
                    }
                    ptr = ptr->proximo;
                }
                if(ptr == NULL) ///caso o ponteiro seja NULL, ele percorreu a lista inteira e o c�digo n�o foi encontrado
                {
                    printf("\nC�digo inv�lido\n\nDigite novamente: ");
                    counter = 1;
                }
            }
            while(counter == 1); ///foi definido uma vari�vel para que caso o c�digo n�o exista, precise digitar novamente

            counter = 0;
            printf("\nDigite a quantidade que deseja comprar: ");
            scanf("%d", &quant_item);
            getchar();
            if(quant_item > ptr->produto->quant_estoque) ///verifica se a quantidade escolhida est� dispon�vel no estoque
            {
                printf("\nQuantidade de item indispon�vel no estoque\n");
                counter = 1;
                printf("\nPressione [ENTER] para voltar");
                getchar();
            }
            else if(quant_item < 0) ///verifica se a quantidade escolhida � maior que 0, caso n�o for, a quantidade � inv�lida
            {
                printf("\nQuantidade inv�lida\n");
                counter = 1;
                printf("\nPressione [ENTER] para voltar");
                getchar();
            }

            if(counter == 1) ///a mesma vari�vel de antes � definida para conferir se as exig�ncias batem, caso n�o batam abre um menu
            {
                system(CLEAR);
                printf("     C�DIGO  |   OP��O\n\t1\tFinalizar compra\n\t2\tComprar outro item\n\t3\tCancelar compra\n\nDigite o c�digo: ");
                do
                {
                    scanf("%d", &menu);
                    getchar();
                    switch(menu)
                    {
                    case 1:
                        counter = 0;
                        break;

                    case 2:
                        counter = 1;
                        break;

                    case 3:
                        leitura_arquivo(lista);
                        lista->inicio2 = NULL;
                        vendas(lista);
                        break;

                    default:
                        printf("C�digo inv�lido\nDigite o c�digo novamente: ");
                    }
                }
                while(menu < 1 || menu > 3);
            }
        }
        while(counter == 1); ///a mesma vari�vel de antes � definida para conferir se as exig�ncias batem

        if((quant_item > 0) && (quant_item <= ptr->produto->quant_estoque)) ///se a quantidade escolhida for maior que zero e menor ou igual a dispon�vel no estoque, ele completa a compra
        {
            ptr->produto->quant_estoque -= quant_item; ///diminui a quantidade no estoque
            ptr->produto->quant_vendida += quant_item; ///aumenta a quantidade de itens vendidos

            valor_total += ptr->produto->valor_unit * quant_item; ///soma o valor total da compra

            novo = (No2*) malloc(sizeof(No2)); ///cria um bloco de mem�ria para o N� da compra
            novo->vendido = (Vendido*) malloc(sizeof(Vendido)); ///cria um bloco de mem�ria para a compra

            strcpy(novo->vendido->nome, ptr->produto->nome); ///copia o nome do item da lista de produtos para o item da lista de compras
            novo->vendido->quant_vendida = quant_item; ///salva a quantidade vendida no bloco de mem�ria
            novo->vendido->valor_unit = ptr->produto->valor_unit; ///passa o valor do produto para o item vendido
            novo->vendido->subtotal = novo->vendido->valor_unit * quant_item; ///faz o c�lculo do subtotal de cada compra e salva no bloco de mem�ria

            insere2(lista, novo); ///insere o novo n� na lista encadeada de compras
            free(novo); ///libera o bloco mem�ria
        }

        system(CLEAR);
        printf("Deseja realizar outra venda?\n\n     C�DIGO  |   OP��O\n\t1\t  Sim\n\t2\t  N�o\n\nDigite o c�digo: ");
        do
        {
            scanf("%d", &menu);
            getchar();
            if(menu == 1)
                repete = 1;

            else if(menu == 2)
                repete = 0;

            else
                printf("\nC�digo inv�lido\n\nDigite o c�digo novamente: ");
        }
        while((menu > 2) || (menu < 1));
    }
    while(repete == 1); ///vari�vel para verificar se deseja ou n�o comprar um novo item

    system(CLEAR);
    imprime2(lista); ///imprime a nota fiscal
    printf("                                                            TOTAL:    |    R$%.2f\n", valor_total);
    printf("\nPressione [ENTER] para continuar");
    getchar();

    return(valor_total); ///retorna o valor total das compras
    vendas(lista);
}

void valor_troco(float valor_total_desc,float valor_total, Lista *lista) ///Fun��o para calcular o troco
{
    float valor_pago, troco;
    system(CLEAR);

    printf("Valor total: %.2f\n", valor_total_desc);

    printf("Digite o valor pago: ");
    scanf("%f", &valor_pago);
    troco = valor_pago - valor_total_desc; ///c�lculo do troco

    if (troco >= 0) ///verifica se o troco � maior ou igual a zero
    {
        printf("\nTroco: %.2f\n", troco);
        printf("\nCompra finalizada\n");
        printf("\nPressione [ENTER] para continuar");
        getchar();
        getchar();
    }
    else ///caso o troco n�o seja suficiente, precisa colocar um novo modo de pagamento
    {
        printf("\nValor insuficiente\n");
        printf("\nPressione [ENTER] para continuar");
        getchar();
        getchar();
        pagamento(valor_total, lista);
    }

    salvamento_data(lista); ///Fun��o que salva o hist�rico de compras
    salvamento_arquivo(lista); ///Fun��o que salva as altera��es nos produtos
}

void vista(float valor_total, Lista *lista) ///Fun��o caso o pagamento seja a vista
{
    int troco;
    float diferenca = 0, valor_total_desc;
    system(CLEAR);

    valor_total_desc = valor_total;

    if (valor_total < 50) ///verifica se o valor total � menor que 50
    {
        printf ("Desconto de 5%%\n");
        diferenca = valor_total * 0.05; ///calcula o desconto
    }

    else if (valor_total >= 50 && valor_total < 100) ///verifica se o valor total � maior ou igual a 50 e menor que 100
    {
        printf ("Desconto de 10%%\n");
        diferenca = valor_total * 0.1; ///calcula o desconto
    }

    else ///caso seja maior ou igual a 100
    {
        printf ("Desconto de 18%%\n");
        diferenca = valor_total * 0.18; ///calcula o desconto
    }

    valor_total_desc -= diferenca; ///calcula o valor total com desconto
    printf("\nValor total: %.2f\n", valor_total_desc);

    do
    {
        printf("\nTroco � necess�rio?\n\n     C�DIGO  |   OP��O\n\t1\t  Sim\n\t2\t  N�o\n\nDigite o c�digo: ");
        scanf("%d", &troco);
        getchar();

        if(troco == 1)
            valor_troco(valor_total_desc,valor_total, lista); ///chama a fun��o de troco

        else if(troco == 2)
        {
            printf("\nCompra finalizada\n");

            printf("\nPressione [ENTER] para continuar");
            getchar();
        }

        else
            printf("\nC�digo incorreto\n");
    }
    while(troco < 1 || troco > 2);

    salvamento_data(lista); ///Fun��o que salva o hist�rico de compras
    salvamento_arquivo(lista); ///Fun��o que salva as altera��es nos produtos
}

void prazo(float valor_total, Lista *lista) ///Fun��o de pagamento a prazo
{
    int parcela;
    float diferenca = 0, valor_mensal;
    system(CLEAR);

    printf("Digite quantas parcelas: ");
    do
    {
        scanf("%d", &parcela);
        getchar();
        system(CLEAR);

        if ((parcela >= 1)&&(parcela <= 3)) ///verifica se a parcela � maior ou igual a 1, e menor ou igual a 3
        {
            printf ("Acr�scimo de 5%%\n");
            diferenca = valor_total * 0.05; ///calcula o acr�scimo

            valor_total += diferenca; ///calcula o valor total com acr�scimo
            valor_mensal = valor_total / parcela; ///calcula o valor mensal pago

            printf ("\nValor total: %.2f\n", valor_total);
            printf ("Valor parcela: %.2f\n", valor_mensal);
        }

        else if (parcela > 3)
        {
            printf ("Acr�scimo de 8%%\n");
            diferenca = valor_total * 0.08; ///calcula o acr�scimo

            valor_total += diferenca; ///calcula o valor total com acr�scimo
            valor_mensal = valor_total / parcela; ///calcula o valor mensal pago

            printf ("\nValor total: %.2f\n", valor_total);
            printf ("Valor parcela: %.2f\n", valor_mensal);
        }
        else
            printf("\nN�mero de parcelas inv�lido\n\nDigite um valor igual ou acima de 1 parcela: ");
    }
    while(parcela < 1); ///n�o sai do loop enquanto o numero de parcelas n�o for maior ou igual a 1

    printf("\nCompra finalizada\n");

    printf("\nPressione [ENTER] para continuar");
    getchar();

    salvamento_data(lista); ///Fun��o que salva o hist�rico de compras
    salvamento_arquivo(lista); ///Fun��o que salva as altera��es nos produtos
}

void pagamento(float valor_total, Lista *lista) ///Fun��o para escolher a forma de pagamento
{
    system(CLEAR);
    int modo_pagamento;

    printf("Formas de pagamento:\n\n     C�DIGO  |   OP��O\n\t1\t� vista\n\t2\tA prazo\n\nDigite o c�digo: ");
    scanf("%d", &modo_pagamento);
    getchar();

    if (modo_pagamento == 1)
    {
        printf("\nPagamento � vista\n");
        vista(valor_total, lista);
    }

    else if (modo_pagamento == 2)
    {
        printf("\nPagamento a prazo\n");
        prazo(valor_total, lista);
    }
    else
    {
        printf("\nOp��o de pagamento inv�lida\n");
        printf("\nPressione [ENTER] para continuar");
        getchar();
        pagamento(valor_total, lista);
    }
}

void relatorio_vendas(Lista *lista) ///Fun��o para imprimir o relat�rio de vendas
{
    No *ptr = lista->inicio; ///declara��o do ponteiro que vai percorrer a lista de produtos
    system(CLEAR);
    puts("        C�DIGO       |           NOME           |    ESTOQUE    |    VENDIDOS");
    while(ptr != NULL)
    {
        printf("\t%-10lu     %-25s       %3d\t       %3d\n", ptr->produto->codigo,  ptr->produto->nome,  ptr->produto->quant_estoque, ptr->produto->quant_vendida);

        ptr = ptr->proximo;
    }
}

void vendas(Lista *lista) ///Fun��o respons�vel pelo menu das vendas
{
    int opcao = 0, counter = 1;
    float valor_total;
    do
    {
        system(CLEAR);
        printf("     C�DIGO  |   OP��O\n\t1\tRealizar vendas\n\t2\tRelat�rio de vendas\n\t3\tVoltar\n\nDigite um c�digo: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 1)
        {
            if(lista->inicio == NULL)
            {
                system(CLEAR);
                puts("N�o h� produtos na lista.");
                printf("\nPressione [ENTER] para continuar");
                getchar();
            }
            else
            {
                valor_total = realizar_vendas(lista);
                pagamento(valor_total, lista);
            }
        }

        else if(opcao == 2)
        {
            if(lista->inicio == NULL)
            {
                system(CLEAR);
                puts("N�o h� produtos na lista.");
                printf("\nPressione [ENTER] para continuar");
                getchar();
            }
            else
            {
                relatorio_vendas(lista);
                printf("\nPressione [ENTER] para continuar");
                getchar();
            }
        }

        else if(opcao == 3)
            counter = 0;

        else
        {
            printf("\nC�digo inv�lido\n\n");
            printf("\nPressione [ENTER] para continuar");
            getchar();
        }
    }
    while(counter == 1);
}
