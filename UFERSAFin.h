#ifndef H_UFERSAFIN
#define H_UFERSAFIN

typedef struct Usuarios usuarios;

int menulogin();

void cadastrarusuario();

int login();

typedef struct Gastos gastos;

typedef struct no No;

typedef struct lista Lista;

void adicionaFim(Lista *lista, gastos e);

void liberarLista(Lista *lista);

void deletar(Lista *lista, char nome[20]);

int menusistema();

void cadastrar();

void listar();

int tamanho();

void editar();

void excluir();

void buscar();

void listarcategoria();

typedef struct Categorias categorias;

typedef struct no2 No2;

typedef struct lista2 Lista2;

void adicionaFim2(Lista2 *lista2, categorias e);

void liberarLista2(Lista2 *lista2);

void resumo();

void definirlimite();

void gastoxlimite();

void maiorparamenor();

void iniciarnovamente();

#endif