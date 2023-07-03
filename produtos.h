#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED

///Define a palavra CLEAR para ficar viável tanto no windows, quanto no Linux
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct Produto ///Struct dos produtos
{
    unsigned long int codigo;
    char nome[25];
    float valor_unit;
    int quant_estoque;
    int quant_vendida;
}Produto;

typedef struct Vendido ///Struct das vendas
{
    char nome[25];
    float valor_unit;
    int quant_vendida;
    float subtotal;
}Vendido;

typedef struct No ///Node dos produtos
{
    Produto *produto;
    struct No *proximo;
    struct No *anterior;
}No;

typedef struct No2 ///Node das vendas
{
    Vendido *vendido;
    struct No2 *proximo;
    struct No2 *anterior;
}No2;

typedef struct Lista ///Struct de definição do inicio das listas
{
    No *inicio;
    No2 *inicio2;
}Lista;

void salvamento_data(Lista *lista);
void salvamento_arquivo(Lista *lista);
void leitura_arquivo(Lista *lista);
void insere(Lista *lista, No* cadastro);
void imprime(Lista *lista, unsigned long int codigo);
void remover(Lista *lsita, No *ptr);
void insere2(Lista *lista, No2* cadastro);
void imprime2(Lista *lista);
void funcao_produto(Lista *lista);
void vendas(Lista *lista);

#endif
