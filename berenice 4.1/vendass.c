#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"

///Arquivo responsável pelas vendas

float realizar_vendas(Lista *lista) ///Função de compra
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
            printf("\nDigite o código do item escolhido: ");
            do
            {
                ptr = lista->inicio;
                scanf("%lu", &codigo);
                getchar();

                while(ptr != NULL)
                {
                    if(codigo == ptr->produto->codigo) ///verifica se o código digitado existe, caso exista, sai do while
                    {
                        counter = 0;
                        break;
                    }
                    ptr = ptr->proximo;
                }
                if(ptr == NULL) ///caso o ponteiro seja NULL, ele percorreu a lista inteira e o código não foi encontrado
                {
                    printf("\nCódigo inválido\n\nDigite novamente: ");
                    counter = 1;
                }
            }
            while(counter == 1); ///foi definido uma variável para que caso o código não exista, precise digitar novamente

            counter = 0;
            printf("\nDigite a quantidade que deseja comprar: ");
            scanf("%d", &quant_item);
            getchar();
            if(quant_item > ptr->produto->quant_estoque) ///verifica se a quantidade escolhida está disponível no estoque
            {
                printf("\nQuantidade de item indisponível no estoque\n");
                counter = 1;
                printf("\nPressione [ENTER] para voltar");
                getchar();
            }
            else if(quant_item < 0) ///verifica se a quantidade escolhida é maior que 0, caso não for, a quantidade é inválida
            {
                printf("\nQuantidade inválida\n");
                counter = 1;
                printf("\nPressione [ENTER] para voltar");
                getchar();
            }

            if(counter == 1) ///a mesma variável de antes é definida para conferir se as exigências batem, caso não batam abre um menu
            {
                system(CLEAR);
                printf("     CÓDIGO  |   OPÇÃO\n\t1\tFinalizar compra\n\t2\tComprar outro item\n\t3\tCancelar compra\n\nDigite o código: ");
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
                        printf("Código inválido\nDigite o código novamente: ");
                    }
                }
                while(menu < 1 || menu > 3);
            }
        }
        while(counter == 1); ///a mesma variável de antes é definida para conferir se as exigências batem

        if((quant_item > 0) && (quant_item <= ptr->produto->quant_estoque)) ///se a quantidade escolhida for maior que zero e menor ou igual a disponível no estoque, ele completa a compra
        {
            ptr->produto->quant_estoque -= quant_item; ///diminui a quantidade no estoque
            ptr->produto->quant_vendida += quant_item; ///aumenta a quantidade de itens vendidos

            valor_total += ptr->produto->valor_unit * quant_item; ///soma o valor total da compra

            novo = (No2*) malloc(sizeof(No2)); ///cria um bloco de memória para o Nó da compra
            novo->vendido = (Vendido*) malloc(sizeof(Vendido)); ///cria um bloco de memória para a compra

            strcpy(novo->vendido->nome, ptr->produto->nome); ///copia o nome do item da lista de produtos para o item da lista de compras
            novo->vendido->quant_vendida = quant_item; ///salva a quantidade vendida no bloco de memória
            novo->vendido->valor_unit = ptr->produto->valor_unit; ///passa o valor do produto para o item vendido
            novo->vendido->subtotal = novo->vendido->valor_unit * quant_item; ///faz o cálculo do subtotal de cada compra e salva no bloco de memória

            insere2(lista, novo); ///insere o novo nó na lista encadeada de compras
            free(novo); ///libera o bloco memória
        }

        system(CLEAR);
        printf("Deseja realizar outra venda?\n\n     CÓDIGO  |   OPÇÃO\n\t1\t  Sim\n\t2\t  Não\n\nDigite o código: ");
        do
        {
            scanf("%d", &menu);
            getchar();
            if(menu == 1)
                repete = 1;

            else if(menu == 2)
                repete = 0;

            else
                printf("\nCódigo inválido\n\nDigite o código novamente: ");
        }
        while((menu > 2) || (menu < 1));
    }
    while(repete == 1); ///variável para verificar se deseja ou não comprar um novo item

    system(CLEAR);
    imprime2(lista); ///imprime a nota fiscal
    printf("                                                            TOTAL:    |    R$%.2f\n", valor_total);
    printf("\nPressione [ENTER] para continuar");
    getchar();

    return(valor_total); ///retorna o valor total das compras
    vendas(lista);
}

void valor_troco(float valor_total_desc,float valor_total, Lista *lista) ///Função para calcular o troco
{
    float valor_pago, troco;
    system(CLEAR);

    printf("Valor total: %.2f\n", valor_total_desc);

    printf("Digite o valor pago: ");
    scanf("%f", &valor_pago);
    troco = valor_pago - valor_total_desc; ///cálculo do troco

    if (troco >= 0) ///verifica se o troco é maior ou igual a zero
    {
        printf("\nTroco: %.2f\n", troco);
        printf("\nCompra finalizada\n");
        printf("\nPressione [ENTER] para continuar");
        getchar();
        getchar();
    }
    else ///caso o troco não seja suficiente, precisa colocar um novo modo de pagamento
    {
        printf("\nValor insuficiente\n");
        printf("\nPressione [ENTER] para continuar");
        getchar();
        getchar();
        pagamento(valor_total, lista);
    }

    salvamento_data(lista); ///Função que salva o histórico de compras
    salvamento_arquivo(lista); ///Função que salva as alterações nos produtos
}

void vista(float valor_total, Lista *lista) ///Função caso o pagamento seja a vista
{
    int troco;
    float diferenca = 0, valor_total_desc;
    system(CLEAR);

    valor_total_desc = valor_total;

    if (valor_total < 50) ///verifica se o valor total é menor que 50
    {
        printf ("Desconto de 5%%\n");
        diferenca = valor_total * 0.05; ///calcula o desconto
    }

    else if (valor_total >= 50 && valor_total < 100) ///verifica se o valor total é maior ou igual a 50 e menor que 100
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
        printf("\nTroco é necessário?\n\n     CÓDIGO  |   OPÇÃO\n\t1\t  Sim\n\t2\t  Não\n\nDigite o código: ");
        scanf("%d", &troco);
        getchar();

        if(troco == 1)
            valor_troco(valor_total_desc,valor_total, lista); ///chama a função de troco

        else if(troco == 2)
        {
            printf("\nCompra finalizada\n");

            printf("\nPressione [ENTER] para continuar");
            getchar();
        }

        else
            printf("\nCódigo incorreto\n");
    }
    while(troco < 1 || troco > 2);

    salvamento_data(lista); ///Função que salva o histórico de compras
    salvamento_arquivo(lista); ///Função que salva as alterações nos produtos
}

void prazo(float valor_total, Lista *lista) ///Função de pagamento a prazo
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

        if ((parcela >= 1)&&(parcela <= 3)) ///verifica se a parcela é maior ou igual a 1, e menor ou igual a 3
        {
            printf ("Acréscimo de 5%%\n");
            diferenca = valor_total * 0.05; ///calcula o acréscimo

            valor_total += diferenca; ///calcula o valor total com acréscimo
            valor_mensal = valor_total / parcela; ///calcula o valor mensal pago

            printf ("\nValor total: %.2f\n", valor_total);
            printf ("Valor parcela: %.2f\n", valor_mensal);
        }

        else if (parcela > 3)
        {
            printf ("Acréscimo de 8%%\n");
            diferenca = valor_total * 0.08; ///calcula o acréscimo

            valor_total += diferenca; ///calcula o valor total com acréscimo
            valor_mensal = valor_total / parcela; ///calcula o valor mensal pago

            printf ("\nValor total: %.2f\n", valor_total);
            printf ("Valor parcela: %.2f\n", valor_mensal);
        }
        else
            printf("\nNúmero de parcelas inválido\n\nDigite um valor igual ou acima de 1 parcela: ");
    }
    while(parcela < 1); ///não sai do loop enquanto o numero de parcelas não for maior ou igual a 1

    printf("\nCompra finalizada\n");

    printf("\nPressione [ENTER] para continuar");
    getchar();

    salvamento_data(lista); ///Função que salva o histórico de compras
    salvamento_arquivo(lista); ///Função que salva as alterações nos produtos
}

void pagamento(float valor_total, Lista *lista) ///Função para escolher a forma de pagamento
{
    system(CLEAR);
    int modo_pagamento;

    printf("Formas de pagamento:\n\n     CÓDIGO  |   OPÇÃO\n\t1\tÀ vista\n\t2\tA prazo\n\nDigite o código: ");
    scanf("%d", &modo_pagamento);
    getchar();

    if (modo_pagamento == 1)
    {
        printf("\nPagamento à vista\n");
        vista(valor_total, lista);
    }

    else if (modo_pagamento == 2)
    {
        printf("\nPagamento a prazo\n");
        prazo(valor_total, lista);
    }
    else
    {
        printf("\nOpção de pagamento inválida\n");
        printf("\nPressione [ENTER] para continuar");
        getchar();
        pagamento(valor_total, lista);
    }
}

void relatorio_vendas(Lista *lista) ///Função para imprimir o relatório de vendas
{
    No *ptr = lista->inicio; ///declaração do ponteiro que vai percorrer a lista de produtos
    system(CLEAR);
    puts("        CÓDIGO       |           NOME           |    ESTOQUE    |    VENDIDOS");
    while(ptr != NULL)
    {
        printf("\t%-10lu     %-25s       %3d\t       %3d\n", ptr->produto->codigo,  ptr->produto->nome,  ptr->produto->quant_estoque, ptr->produto->quant_vendida);

        ptr = ptr->proximo;
    }
}

void vendas(Lista *lista) ///Função responsável pelo menu das vendas
{
    int opcao = 0, counter = 1;
    float valor_total;
    do
    {
        system(CLEAR);
        printf("     CÓDIGO  |   OPÇÃO\n\t1\tRealizar vendas\n\t2\tRelatório de vendas\n\t3\tVoltar\n\nDigite um código: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 1)
        {
            if(lista->inicio == NULL)
            {
                system(CLEAR);
                puts("Não há produtos na lista.");
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
                puts("Não há produtos na lista.");
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
            printf("\nCódigo inválido\n\n");
            printf("\nPressione [ENTER] para continuar");
            getchar();
        }
    }
    while(counter == 1);
}
