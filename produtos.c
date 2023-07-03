#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Produtos.h"

///Arquivo responsável pelo menu produto, ele faz desde a criação, atualização, até exclusão dos produtos

void novo_produto(Lista *lista) ///Função para cadastrar um novo produto
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
            printf("\nEstá tentando adicionar zero ou menos itens\nDigite um valor maior que zero: ");
    }
    while(quant <= 0);

    for(int i = 0; i < quant; i++)
    {
        system(CLEAR);
        int counter;
        cadastro = (No*) malloc(sizeof(No)); ///alocação dinâmica do Node do novo produto
        cadastro->produto = (Produto*) malloc(sizeof(Produto)); ///alocação dinâmica das informações do novo produto
        printf("Digite o código do item: ");
        do
        {
            scanf("%lu", &cadastro->produto->codigo); ///o código está sendo definido como unsigned long int
            getchar();

            ptr = lista->inicio; ///define um ponteiro para percorrer a lista
            counter = 0;
            while(ptr != NULL) ///está verificando se o código já foi usado anteriormente, não pode haver código idênticos
            {
                if(cadastro->produto->codigo == ptr->produto->codigo)
                {
                    counter = 1;
                    printf("\nCódigo já em uso\nDigite um código novo: ");
                }
                ptr = ptr->proximo;
            }
        }
        while(counter == 1); ///foi definido uma variável para que sempre que o código já existir, ter que digitar um novo

        printf("\nDigite o nome do item: ");
        do
        {
            counter = 0;
            fflush(stdin); ///getchar não funciona direito com string, então deixei um fflush, ele limpa as entradas do teclado, embora não seja recomendado
            gets(cadastro->produto->nome);
            tamanho_str = strlen(cadastro->produto->nome); ///está pegando o tamanho do nome


            for(int j = 0; j < strlen(cadastro->produto->nome); j++) ///esse for está fazendo a verificação de espaços, não pode conter somente espaços no nome
            {
                if(isspace(cadastro->produto->nome[j]) == 0) ///se achar uma letra, ele quebra o for
                {
                    counter = 0;
                    break;
                }
                else
                    counter = 1;
            }
            if(strlen(cadastro->produto->nome) == 0) ///faz a verificação de espaço vazio
                counter = 1;

            else if(tamanho_str > 25) ///faz a verificação de máximo de letras
            {
                printf("\nNome do item muito grande");
                counter = 1;
            }

            if(counter == 1)
                printf("\nDigite novamente: ");
        }
        while(counter == 1); ///a mesma variável de antes é definida para conferir se as exigências batem

        while(isspace(cadastro->produto->nome[0])) ///sempre que começar com espaço, ele vai passar esses espaços antes da palavra para o final
            for(int j = 0; j < strlen(cadastro->produto->nome); j++)
            {
                int aux = cadastro->produto->nome[j];
                cadastro->produto->nome[j] = cadastro->produto->nome[j + 1];
                cadastro->produto->nome[j + 1] = aux;
            }

        printf("\nDigite o preço do item: ");
        do
        {
            counter = 0;
            scanf("%f", &cadastro->produto->valor_unit);
            getchar();
            if(cadastro->produto->valor_unit < 0) ///o valor unitário não pode ser menor que zero
            {
                counter = 1;
                printf("\nValor menor que zero\nDigite um valor maior ou igual a zero: ");
            }
        }
        while(counter == 1); ///a mesma variável de antes é definida para conferir se as exigências batem

        printf("\nDigite a quantidade de estoque do item: ");
        do
        {
            counter = 0;
            scanf("%d", &cadastro->produto->quant_estoque);
            getchar();
            if(cadastro->produto->quant_estoque < 0) ///o estoque não pode ser menor que zero
            {
                counter = 1;
                printf("\nEstoque menor que zero\nDigite um número maior ou igual a zero: ");
            }
        }
        while(counter == 1); ///a mesma variável de antes é definida para conferir se as exigências batem
        cadastro->produto->quant_vendida = 0; ///define a quantidade vendida para zero

        insere(lista, cadastro); ///chama a função para inserir o novo produto na lista encadeada

        system(CLEAR);

        imprime(lista, cadastro->produto->codigo); ///imprime as informações do novo produto

        free(cadastro); ///libera a memória alocada

        puts("");
        puts("Pressione [ENTER] para continuar!");
        getchar();

        system(CLEAR);
        imprime(lista, -1); ///imprime a lista inteira
        puts("\nPressione [ENTER] para voltar");
        getchar();

    }
}

void atualizar(Lista *lista) ///Função para atualizar um produto
{
    unsigned long int codigo;
    int opcao = 0, quant_estoque;
    float valor_unit;

    if(lista->inicio == NULL) ///verifica se a lista está vazia
    {
        puts("Não há produtos na lista.");
        return;
    }
    else
    {
        imprime(lista, -1); ///chama a função que imprime a lista de produtos
        printf("\nDigite o código do item que deseja atualizar: ");
        scanf("%lu", &codigo); ///guarda em uma variável o código do produto que a pessoa digitou
        getchar();

        No *ptr = lista->inicio; ///define um ponteiro para percorrer a lista

        while (ptr != NULL)
        {
            if (ptr->produto->codigo == codigo) ///caso ache um código de produto igual ao que foi digitado
            {
                system(CLEAR);
                imprime(lista, codigo); ///imprime o produto que a pessoa digitou
                puts("");
                printf("Digite a nova quantidade no estoque: ");
                scanf("%d", &quant_estoque);
                getchar();
                printf("\nDigite o novo preço do produto: ");
                scanf("%f", &valor_unit);
                getchar();
                system(CLEAR);
                puts("        CÓDIGO       |           NOME           |    VALOR    |    ESTOQUE");
                printf("ANTES:\t%-10lu     %-25s     %4.2f\t    %3d\n\n", ptr->produto->codigo, ptr->produto->nome, ptr->produto->valor_unit, ptr->produto->quant_estoque);
                printf("DEPOIS:\t%-10lu     %-25s     %4.2f\t    %3d\n", ptr->produto->codigo, ptr->produto->nome, valor_unit, quant_estoque);
                puts("");
                printf("Deseja confirmar alteração?\n\n     CÓDIGO  |   OPÇÃO\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma opção: ");
                do
                {
                    scanf("%d", &opcao);
                    getchar();
                    if(opcao == 1) ///guarda as atualizações
                    {
                        ptr->produto->quant_estoque = quant_estoque;
                        ptr->produto->valor_unit = valor_unit;
                        puts("\nItem atualizado com sucesso!");
                        return;
                    }

                    else if(opcao == 2) ///caso cancele, não altera
                        break;

                    else
                        printf("\nEscolha uma opção válida\nDigite novamente: ");
                }
                while(opcao < 1 || opcao > 2);
            }
            if(ptr == NULL)
                puts("\nProduto não encontrado");

            ptr = ptr->proximo;
        }
    }
}

void excluir(Lista *lista) ///Função chamada para excluir um produto da lista
{
    unsigned long int codigo;
    int opcao;

    imprime(lista, -1); ///chama a função para imprimir a lista inteira

    printf("\nDigite o código do item que deseja excluir: ");
    scanf("%lu", &codigo);
    getchar();

    if(lista->inicio == NULL) ///Caso a lista estiver vazia, imprime e retorna
    {
        system(CLEAR);
        puts("Não há produtos na lista.");
        puts("\nPressione [ENTER] para voltar");
        getchar();
        return;
    }

    else
    {
        No *ptr = lista->inicio; ///define um ponteiro que percorre a lista

        while(ptr != NULL && ptr->produto->codigo != codigo) ///percorre a lista até achar um código de produto que exista na lista
            ptr = ptr->proximo;

        if(ptr == NULL) ///se não encontrar, imprime e retorna
        {
            system(CLEAR);
            puts("Código não encontado");
            puts("\nPressione [ENTER] para voltar");
            getchar();
            return;
        }
        else
        {
            system(CLEAR);
            imprime(lista, codigo); ///imprime o produto específico
            printf("\nDeseja excluir este item?\n\n     CÓDIGO  |   OPÇÃO\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma opção: ");
            do
            {
                scanf("%d", &opcao);
                getchar();
                if(opcao == 1)
                {
                    remover(lista, ptr); ///chama a função de remoção da lista
                    system(CLEAR);
                    imprime(lista, -1);
                    puts("\nItem removido!");
                }
                else if(opcao == 2) {} ///caso cancele, nada acontece
                else
                    printf("\nEscolha uma opção válida\nDigite novamente: ");
            }
            while(opcao < 1 || opcao > 2);
        }
    }
}

void funcao_produto(Lista *lista)  ///Função de menu de alteração dos produtos
{
    system(CLEAR);
    int opcao = 0, salvo = 1, opcao_salvar = 0;

    printf("     CÓDIGO  |   OPÇÃO\n\t1\tExibir\n\t2\tCadastrar\n\t3\tAtualizar\n\t4\tExcluir\n\t5\tSalvar\n\t6\tLer\n\t7\tVoltar\n\nDigite um código: ");
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
            salvamento_arquivo(lista); ///chama a função que salva os novos produtos no arquivo
            puts("Salvo com sucesso!\n\nPressione [ENTER] para continuar");
            getchar();
            break;

        case 6:
            salvo = 1;
            system(CLEAR);
            leitura_arquivo(lista); ///chama a função que lê os produtos do arquivo
            printf("Lido com sucesso!\n\nPressione [ENTER] para voltar");
            getchar();
            break;

        case 7: ///caso escolha a opção salvar, e não foi salvo depois da última atualização, pergunta se deseja que salve
            if(salvo == 1)
            {
                system(CLEAR);
                printf("Deseja salvar antes de sair?\n\n     CÓDIGO  |   OPÇÃO\n\t1\tConfirmar\n\t2\tCancelar\n\nEscolha uma opção: ");
                do
                {
                    scanf("%d", &opcao_salvar);
                    getchar();
                    if(opcao_salvar == 1)
                    {
                        system(CLEAR);
                        salvamento_arquivo(lista); ///chama a função que salva os novos produtos no arquivo
                        puts("Salvo com sucesso!\n\nPressione [ENTER] para continuar");
                        getchar();
                    }
                    else if(opcao_salvar == 2) {}
                    else
                        printf("\nCódigo inválido\nDigite novamente: ");
                }
                while(opcao_salvar < 1 || opcao_salvar > 2);
            }
            return;
            break;

        default:
            printf("\nCódigo inválido\n\nDigite um código válido: ");
        }
    }
    while(opcao < 1 || opcao > 7);

    funcao_produto(lista);
}
