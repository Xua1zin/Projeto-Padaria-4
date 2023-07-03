#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Produtos.h"

///Arquivo respons�vel pelo menu produto, ele faz desde a cria��o, atualiza��o, at� exclus�o dos produtos

void novo_produto(Lista *lista) ///Fun��o para cadastrar um novo produto
{
    system(CLEAR);
    int tamanho_str = 0, quant = 0;
    No *cadastro;
    No *ptr;

    printf("Digite a quantidade de novos itens: ");
    do
    {
        scanf("%d", &quant);
        getchar();
        if(quant <= 0)
            printf("\nEst� tentando adicionar zero ou menos itens\nDigite um valor maior que zero: ");
    }
    while(quant <= 0);

    for(int i = 0; i < quant; i++)
    {
        system(CLEAR);
        int counter;
        cadastro = (No*) malloc(sizeof(No)); ///aloca��o din�mica do Node do novo produto
        cadastro->produto = (Produto*) malloc(sizeof(Produto)); ///aloca��o din�mica das informa��es do novo produto
        printf("Digite o c�digo do item: ");
        do
        {
            scanf("%lu", &cadastro->produto->codigo); ///o c�digo est� sendo definido como unsigned long int
            getchar();

            ptr = lista->inicio; ///define um ponteiro para percorrer a lista
            counter = 0;
            while(ptr != NULL) ///est� verificando se o c�digo j� foi usado anteriormente, n�o pode haver c�digo id�nticos
            {
                if(cadastro->produto->codigo == ptr->produto->codigo)
                {
                    counter = 1;
                    printf("\nC�digo j� em uso\nDigite um c�digo novo: ");
                }
                ptr = ptr->proximo;
            }
        }
        while(counter == 1); ///foi definido uma vari�vel para que sempre que o c�digo j� existir, ter que digitar um novo

        printf("\nDigite o nome do item: ");
        do
        {
            counter = 0;
            fflush(stdin); ///getchar n�o funciona direito com string, ent�o deixei um fflush, ele limpa as entradas do teclado, embora n�o seja recomendado
            gets(cadastro->produto->nome);
            tamanho_str = strlen(cadastro->produto->nome); ///est� pegando o tamanho do nome


            for(int j = 0; j < strlen(cadastro->produto->nome); j++) ///esse for est� fazendo a verifica��o de espa�os, n�o pode conter somente espa�os no nome
            {
                if(isspace(cadastro->produto->nome[j]) == 0) ///se achar uma letra, ele quebra o for
                {
                    counter = 0;
                    break;
                }
                else
                    counter = 1;
            }
            if(strlen(cadastro->produto->nome) == 0) ///faz a verifica��o de espa�o vazio
                counter = 1;

            else if(tamanho_str > 25) ///faz a verifica��o de m�ximo de letras
            {
                printf("\nNome do item muito grande");
                counter = 1;
            }

            if(counter == 1)
                printf("\nDigite novamente: ");
        }
        while(counter == 1); ///a mesma vari�vel de antes � definida para conferir se as exig�ncias batem

        while(isspace(cadastro->produto->nome[0])) ///sempre que come�ar com espa�o, ele vai passar esses espa�os antes da palavra para o final
            for(int j = 0; j < strlen(cadastro->produto->nome); j++)
            {
                int aux = cadastro->produto->nome[j];
                cadastro->produto->nome[j] = cadastro->produto->nome[j + 1];
                cadastro->produto->nome[j + 1] = aux;
            }

        printf("\nDigite o pre�o do item: ");
        do
        {
            counter = 0;
            scanf("%f", &cadastro->produto->valor_unit);
            getchar();
            if(cadastro->produto->valor_unit < 0) ///o valor unit�rio n�o pode ser menor que zero
            {
                counter = 1;
                printf("\nValor menor que zero\nDigite um valor maior ou igual a zero: ");
            }
        }
        while(counter == 1); ///a mesma vari�vel de antes � definida para conferir se as exig�ncias batem

        printf("\nDigite a quantidade de estoque do item: ");
        do
        {
            counter = 0;
            scanf("%d", &cadastro->produto->quant_estoque);
            getchar();
            if(cadastro->produto->quant_estoque < 0) ///o estoque n�o pode ser menor que zero
            {
                counter = 1;
                printf("\nEstoque menor que zero\nDigite um n�mero maior ou igual a zero: ");
            }
        }
        while(counter == 1); ///a mesma vari�vel de antes � definida para conferir se as exig�ncias batem
        cadastro->produto->quant_vendida = 0; ///define a quantidade vendida para zero

        insere(lista, cadastro); ///chama a fun��o para inserir o novo produto na lista encadeada

        system(CLEAR);

        imprime(lista, cadastro->produto->codigo); ///imprime as informa��es do novo produto

        free(cadastro); ///libera a mem�ria alocada

        puts("");
        puts("Pressione [ENTER] para continuar!");
        getchar();

        system(CLEAR);
        imprime(lista, -1); ///imprime a lista inteira
        puts("\nPressione [ENTER] para voltar");
        getchar();

    }
}

void atualizar(Lista *lista) ///Fun��o para atualizar um produto
{
    unsigned long int codigo;
    int opcao = 0, quant_estoque;
    float valor_unit;

    if(lista->inicio == NULL) ///verifica se a lista est� vazia
    {
        puts("N�o h� produtos na lista.");
        return;
    }
    else
    {
        imprime(lista, -1); ///chama a fun��o que imprime a lista de produtos
        printf("\nDigite o c�digo do item que deseja atualizar: ");
        scanf("%lu", &codigo); ///guarda em uma vari�vel o c�digo do produto que a pessoa digitou
        getchar();

        No *ptr = lista->inicio; ///define um ponteiro para percorrer a lista

        while (ptr != NULL)
        {
            if (ptr->produto->codigo == codigo) ///caso ache um c�digo de produto igual ao que foi digitado
            {
                system(CLEAR);
                imprime(lista, codigo); ///imprime o produto que a pessoa digitou
                puts("");
                printf("Digite a nova quantidade no estoque: ");
                scanf("%d", &quant_estoque);
                getchar();
                printf("\nDigite o novo pre�o do produto: ");
                scanf("%f", &valor_unit);
                getchar();
                system(CLEAR);
                puts("        C�DIGO       |           NOME           |    VALOR    |    ESTOQUE");
                printf("ANTES:\t%-10lu     %-25s     %4.2f\t    %3d\n\n", ptr->produto->codigo, ptr->produto->nome, ptr->produto->valor_unit, ptr->produto->quant_estoque);
                printf("DEPOIS:\t%-10lu     %-25s     %4.2f\t    %3d\n", ptr->produto->codigo, ptr->produto->nome, valor_unit, quant_estoque);
                puts("");
                printf("Deseja confirmar altera��o?\n\n     C�DIGO  |   OP��O\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma op��o: ");
                do
                {
                    scanf("%d", &opcao);
                    getchar();
                    if(opcao == 1) ///guarda as atualiza��es
                    {
                        ptr->produto->quant_estoque = quant_estoque;
                        ptr->produto->valor_unit = valor_unit;
                        puts("\nItem atualizado com sucesso!");
                        return;
                    }

                    else if(opcao == 2) ///caso cancele, n�o altera
                        break;

                    else
                        printf("\nEscolha uma op��o v�lida\nDigite novamente: ");
                }
                while(opcao < 1 || opcao > 2);
            }
            if(ptr == NULL)
                puts("\nProduto n�o encontrado");

            ptr = ptr->proximo;
        }
    }
}

void excluir(Lista *lista) ///Fun��o chamada para excluir um produto da lista
{
    unsigned long int codigo;
    int opcao;

    imprime(lista, -1); ///chama a fun��o para imprimir a lista inteira

    printf("\nDigite o c�digo do item que deseja excluir: ");
    scanf("%lu", &codigo);
    getchar();

    if(lista->inicio == NULL) ///Caso a lista estiver vazia, imprime e retorna
    {
        system(CLEAR);
        puts("N�o h� produtos na lista.");
        puts("\nPressione [ENTER] para voltar");
        getchar();
        return;
    }

    else
    {
        No *ptr = lista->inicio; ///define um ponteiro que percorre a lista

        while(ptr != NULL && ptr->produto->codigo != codigo) ///percorre a lista at� achar um c�digo de produto que exista na lista
            ptr = ptr->proximo;

        if(ptr == NULL) ///se n�o encontrar, imprime e retorna
        {
            system(CLEAR);
            puts("C�digo n�o encontado");
            puts("\nPressione [ENTER] para voltar");
            getchar();
            return;
        }
        else
        {
            system(CLEAR);
            imprime(lista, codigo); ///imprime o produto espec�fico
            printf("\nDeseja excluir este item?\n\n     C�DIGO  |   OP��O\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma op��o: ");
            do
            {
                scanf("%d", &opcao);
                getchar();
                if(opcao == 1)
                {
                    remover(lista, ptr); ///chama a fun��o de remo��o da lista
                    system(CLEAR);
                    imprime(lista, -1);
                    puts("\nItem removido!");
                }
                else if(opcao == 2) {} ///caso cancele, nada acontece
                else
                    printf("\nEscolha uma op��o v�lida\nDigite novamente: ");
            }
            while(opcao < 1 || opcao > 2);
        }
    }
}

void funcao_produto(Lista *lista)  ///Fun��o de menu de altera��o dos produtos
{
    system(CLEAR);
    int opcao = 0, salvo = 1, opcao_salvar = 0;

    printf("     C�DIGO  |   OP��O\n\t1\tExibir\n\t2\tCadastrar\n\t3\tAtualizar\n\t4\tExcluir\n\t5\tSalvar\n\t6\tLer\n\t7\tVoltar\n\nDigite um c�digo: ");
    do
    {
        scanf("%d", &opcao);
        getchar();
        switch(opcao)
        {

        case 1:
            system(CLEAR);
            imprime(lista, -1);
            puts("\nPressione [ENTER] para voltar");
            getchar();
            break;

        case 2:
            salvo = 0;
            system(CLEAR);
            novo_produto(lista);
            break;

        case 3:
            salvo = 0;
            system(CLEAR);
            atualizar(lista);
            printf("\nPressione [ENTER] para voltar");
            getchar();
            break;

        case 4:
            salvo = 0;
            system(CLEAR);
            excluir(lista);
            puts("\nPressione [ENTER] para voltar");
            getchar();
            break;

        case 5:
            salvo = 1;
            system(CLEAR);
            salvamento_arquivo(lista); ///chama a fun��o que salva os novos produtos no arquivo
            puts("Salvo com sucesso!\n\nPressione [ENTER] para continuar");
            getchar();
            break;

        case 6:
            salvo = 1;
            system(CLEAR);
            leitura_arquivo(lista); ///chama a fun��o que l� os produtos do arquivo
            printf("Lido com sucesso!\n\nPressione [ENTER] para voltar");
            getchar();
            break;

        case 7: ///caso escolha a op��o salvar, e n�o foi salvo depois da �ltima atualiza��o, pergunta se deseja que salve
            if(salvo == 1)
            {
                system(CLEAR);
                printf("Deseja salvar antes de sair?\n\n     C�DIGO  |   OP��O\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma op��o: ");
                do
                {
                    scanf("%d", &opcao_salvar);
                    getchar();
                    if(opcao_salvar == 1)
                    {
                        system(CLEAR);
                        salvamento_arquivo(lista); ///chama a fun��o que salva os novos produtos no arquivo
                        puts("Salvo com sucesso!\n\nPressione [ENTER] para continuar");
                        getchar();
                    }
                    else if(opcao_salvar == 2) {}
                    else
                        printf("\nC�digo inv�lido\nDigite novamente: ");
                }
                while(opcao_salvar < 1 || opcao_salvar > 2);
            }
            return;
            break;

        default:
            printf("\nC�digo inv�lido\n\nDigite um c�digo v�lido: ");
        }
    }
    while(opcao < 1 || opcao > 7);

    funcao_produto(lista);
}
