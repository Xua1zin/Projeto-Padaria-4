#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "produtos.h"

void salvamento_data(Lista *lista)///função que salva histórico de vendas em formato .txt dentro da pasta do arquivo
{
    FILE *arq_data = NULL;
    char data[23];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(data, sizeof(data), "%d-%d-%d_%d-%d-%d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    arq_data = fopen(data, "w");

    if (arq_data == NULL)
    {
        puts("Erro ao abrir o arquivo de dados");
        exit(1);
    }

    No *ptr = lista->inicio; ///ponteiro que percorre a lista

    fprintf(arq_data, "        CÓDIGO       |           NOME           |    ESTOQUE    |    VENDIDOS\n");
    while (ptr != NULL)
    {
        fprintf(arq_data, "\t%-10lu     %-25s       %3d\t       %3d\n", ptr->produto->codigo,  ptr->produto->nome,  ptr->produto->quant_estoque, ptr->produto->quant_vendida);

        ptr = ptr->proximo;
    }
    free(ptr);
    fclose(arq_data);
}

void salvamento_arquivo(Lista *lista) ///função que salva os dados dos produtos em formato de arquivo binário dentro da pasta
{
    FILE *arq_produtos = NULL;
    arq_produtos = fopen("produtos.bin", "wb");

    if (arq_produtos == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    No *ptr = lista->inicio;

    while(ptr != NULL)
    {
        fwrite(ptr->produto, sizeof(Produto), 1, arq_produtos);

        ptr = ptr->proximo;
    }

    fclose(arq_produtos);
}

void leitura_arquivo(Lista *lista) ///função que lê os dados dos produtos em formato de arquivo binário dentro da pasta
{
    FILE *arq_prod = NULL;

    arq_prod = fopen("produtos.bin", "rb");

    if (arq_prod == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    lista->inicio = NULL;

    Produto produto;

    while(fread(&produto, sizeof(Produto), 1, arq_prod) == 1) ///enquanto a leitura do arquivo for verdadeira, ele permanece no while
    {
        No* novo = (No*) malloc(sizeof(No));
        novo->produto = (Produto*) malloc(sizeof(Produto));

        *novo->produto = produto;

        insere(lista, novo);
    }

    fclose(arq_prod);
}
