#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UFERSAFin.h"

struct Usuarios { 
	char login[20];
	char senha[12];
    char email[100];
};

int menulogin(){
    printf("------------- TELA DE LOGIN --------------\n"); 
    printf("Digite 1 para logar\n");
    printf("Digite 2 para cadastrar um novo usuario\n");
    printf("Digite 0 para sair\n");
    printf("----------------------------\n"); 
    int oplogin;
	scanf("%d", &oplogin);
    return oplogin;
}

void cadastrarusuario() {
    int endvalid = 0;
    while(endvalid == 0){
        int valid = 0;
        FILE* file = fopen("usuarios.b", "rb");
        usuarios usuario;
        printf("\n--------------- CADASTRO DE USUARIO ---------------\n");
        printf("informe o login\n");
        scanf("%s", usuario.login);
        printf("informe a senha\n");
        scanf("%s", usuario.senha);
        printf("informe o email\n");
        scanf("%s", usuario.email);
        if (strlen(usuario.email) > 80 || strchr(usuario.email, '@') == NULL){
            valid = 1;
            printf("Email inválido!\n");
        }
        usuarios usuario0;
        while (fread(&usuario0, sizeof(usuarios), 1, file)){
            if(strcmp(usuario.login, usuario0.login) == 0 || strcmp(usuario.email, usuario0.email) == 0){
                valid = 1;
                printf("Usuario ou email já existe!\n");
            }
        }
        fclose(file);

        if(valid == 0){
            printf("Cadastro concluido com sucesso!\n");
            if ((file = fopen("usuarios.b", "rb")) == NULL) {
                fclose(file);
                file = fopen("usuarios.b", "wb");
            } else {
                fclose(file);
                file = fopen("usuarios.b", "ab");
            }
            fwrite(&usuario, sizeof(usuarios), 1, file);
            fclose(file);
            endvalid = 1;
        }
    }
}

int login(){
    int check = 0;
    usuarios usuario0;
    printf("\n--------------- LOGIN DE USUARIO ---------------\n");
    printf("informe o login\n");
    scanf("%s", usuario0.login);
    printf("informe a senha\n");
    scanf("%s", usuario0.senha);
	FILE* file = fopen("usuarios.b", "rb");
	usuarios usuario;
	while (fread(&usuario, sizeof(usuarios), 1, file)){
		if(strcmp(usuario.login, usuario0.login) == 0 && strcmp(usuario.senha, usuario0.senha) == 0){
			check = 1;
		}
	}
    fclose(file);
    return check;
}

struct Gastos { 
	char nome[20];
	char categoria[20];
    float valor;
};

struct no {
    gastos dado;
    struct no* prox;
};

struct lista {
    No* inicio;
};

void adicionaFim(Lista *lista, gastos e) {
    No* novo = (No*) malloc(sizeof(No));
    novo->dado = e;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    }
    else {
        No* pi;
        for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
}

void liberarLista(Lista *lista) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
}

void deletar(Lista *lista, char nome[20]) {
    if (lista->inicio == NULL) {
        printf("Lista vazia\n");
    }
    else {
        No* pa = NULL;
        No* pi;
        for (pi = lista->inicio; pi->prox != NULL && strcmp(pi->dado.nome, nome) != 0; pi = pi->prox) {
            pa = pi;
        }
        if (pa == NULL) {
            if (strcmp(pi->dado.nome, nome) == 0) {
                lista->inicio = pi->prox;
                free(pi);
            }
            else {
                printf("Gasto nao encontrado\n");
            }
        }
        else {
            if (strcmp(pi->dado.nome, nome) == 0) {
                pa->prox = pi->prox;
                free(pi);
            }
            else {
                printf("Gasto nao encontrado\n");
            }
        }
    }
}

int menusistema(){
    printf("----------------------------\n"); 
    printf("Digite 1 para inserir um novo gasto\n");
    printf("Digite 2 para listar os gastos até o momento\n");
    printf("Digite 3 para editar um gasto\n");
    printf("Digite 4 para excluir um gasto\n");
    printf("Digite 5 para buscar e exibir um gasto\n");
    printf("Digite 6 para listar os gastos de uma categoria especifica\n");
    printf("Digite 7 para exibir um resumo dos gastos por categoria\n");
    printf("Digite 8 para inserir/substituir o limite nos gastos\n");
    printf("Digite 9 para exibir o total gasto comparado com o limite\n");
    printf("Digite 10 para exibir os gastos ordenados do maior para o menor\n");
    printf("Digite 11 para excluir todos os gastos e iniciar novamente\n");
    printf("Digite 0 para sair\n");
    printf("----------------------------\n"); 
    int opsistema;
	scanf("%d", &opsistema);
    return opsistema;
}

void cadastrar(){
    int valid = 1;
    while(valid != 0){  
        int valid2 = 0;  
        gastos gasto;
        printf("\n--------------- CADASTRO DE GASTO ---------------\n");   
        printf("informe o nome\n");
        scanf("%s", gasto.nome);
        printf("informe a categoria\n");
        scanf("%s", gasto.categoria);
        printf("informe o valor\n");
        scanf("%f", &gasto.valor);
        FILE* file;
        file = fopen("gastos.b", "rb");
        gastos gasto0;
        while (fread(&gasto0, sizeof(gastos), 1, file)){
            if(strcmp(gasto.nome, gasto0.nome) == 0){
                valid2 = 1;
                printf("Ja existe um gasto com esse nome, caso seja a mesma coisa, coloque um numero no final, Ex: Roupa2\n");
            }
        }
        fclose(file);
        if(valid2 == 1){
            valid = 1;
        }else{
            if ((file = fopen("gastos.b", "rb")) == NULL) {
                fclose(file);
                file = fopen("gastos.b", "wb");
            } else {
                fclose(file);
                file = fopen("gastos.b", "ab");
            }
            fwrite(&gasto, sizeof(gastos), 1, file);
            fclose(file);
            valid = 0;
        }
    }
}

void listar(){
    gastos gasto;
    FILE* file = fopen("gastos.b", "rb");
    printf("nome, categoria, valor (em reais):\n");
    while (fread(&gasto, sizeof(gastos), 1, file)){
        printf("%s, %s, %f\n", gasto.nome, gasto.categoria, gasto.valor);
    }
    fclose(file);
}

int tamanho(){
    int t = 0;
    gastos gasto;
    FILE* file = fopen("gastos.b", "rb");
    while (fread(&gasto, sizeof(gastos), 1, file)){
        t ++;
    }
    return t;
}

void editar(){
    Lista lista;
    lista.inicio = NULL;
    gastos gasto;
    char nome[20];
    printf("Digite o nome do gasto que você deseja editar:\n");
    scanf("%s", nome);
    printf("--------- MENU DE EDIÇÃO ---------\n");
    printf("Digite 1 para editar o nome\n");
    printf("Digite 2 para editar a categoria\n");
    printf("Digite 3 para editar o valor\n");
    printf("-----------------------------------\n");
    int op;
    scanf("%d", &op);
    FILE* file = fopen("gastos.b", "rb");
    while (fread(&gasto, sizeof(gastos), 1, file)) {
        adicionaFim(&lista, gasto);
    }
    fclose(file);
    if (op == 1){
        printf("Digite o novo nome\n");
        char nnome[20];
        scanf("%s", nnome);
        if (lista.inicio == NULL) {
            printf("Lista vazia\n");
        }
        else{
            No* pi;
            for (pi = lista.inicio; pi != NULL && strcmp(pi->dado.nome, nome) != 0; pi = pi->prox);
            if(pi == NULL) {
                printf("Gasto não encontrado\n");
            }
            else {
                strcpy(pi->dado.nome, nnome);
                No* pi;
                file = fopen("gastos.b", "wb");
                for(pi = lista.inicio; pi != NULL; pi = pi->prox){
                    fwrite(&pi->dado, sizeof(gastos), 1, file);
                }
                fclose(file);
                printf("Gasto editado com sucesso!\n");
                }
            }
        }
    else if(op == 2){
        printf("Digite a nova categoria\n");
        char ncategoria[20];
        scanf("%s", ncategoria);
        if (lista.inicio == NULL) {
            printf("Lista vazia\n");
        }
        else{
            No* pi;
            for (pi = lista.inicio; pi != NULL && strcmp(pi->dado.nome, nome) != 0; pi = pi->prox);
            if(pi == NULL) {
                printf("Gasto não encontrado\n");
            }
            else {
                strcpy(pi->dado.categoria, ncategoria);
                No* pi;
                file = fopen("gastos.b", "wb");
                for(pi = lista.inicio; pi != NULL; pi = pi->prox){
                    fwrite(&pi->dado, sizeof(gastos), 1, file);
                }
                fclose(file);
                printf("Gasto editado com sucesso!\n");
                }
            }
        }
    else if(op == 3){
        printf("Digite o novo valor\n");
        float nvalor;
        scanf("%f", &nvalor);
        if (lista.inicio == NULL) {
            printf("Lista vazia\n");
        }
        else{
            No* pi;
            for (pi = lista.inicio; pi != NULL && strcmp(pi->dado.nome, nome) != 0; pi = pi->prox);
            if(pi == NULL) {
                printf("Gasto não encontrado\n");
            }
            else {
                pi->dado.valor = nvalor;
                No* pi;
                file = fopen("gastos.b", "wb");
                for(pi = lista.inicio; pi != NULL; pi = pi->prox){
                    fwrite(&pi->dado, sizeof(gastos), 1, file);
                }
                fclose(file);
                printf("Gasto editado com sucesso!\n");
                }
            }
        }
    liberarLista(&lista);
}

void excluir(){
    Lista lista;
    lista.inicio = NULL;
    gastos gasto;
    char nome[20];
    printf("Digite o nome do gasto que você deseja excluir:\n");
    scanf("%s", nome);
    FILE* file = fopen("gastos.b", "rb");
    while (fread(&gasto, sizeof(gastos), 1, file)) {
        adicionaFim(&lista, gasto);
    }
    fclose(file);
    file = fopen("gastos.b", "wb");
    deletar(&lista, nome);
    No* pi;
    for(pi = lista.inicio; pi != NULL; pi = pi->prox){
        fwrite(&pi->dado, sizeof(gastos), 1, file);
    }
    fclose(file);
    printf("Gasto excluido com sucesso!\n");
    liberarLista(&lista);
}

void buscar(){
    int valid = 0;
    gastos gasto;
    char nome[20];
    printf("Digite o nome do gasto que você deseja exibir:\n");
    scanf("%s", nome);
    FILE* file = fopen("gastos.b", "rb");
    while(fread(&gasto, sizeof(gastos), 1, file)){
		    if(strcmp(gasto.nome, nome) == 0){
                printf("nome, categoria, valor (em reais):\n");
                printf("%s, %s, %f\n", gasto.nome, gasto.categoria, gasto.valor);
                valid = 1;
            }
        }
    if(valid == 0){
        printf("Gasto não encontrado!\n");
    }
    fclose(file);
}

void listarcategoria(){
    int valid = 0;
    gastos gasto;
    char categoria[20];
    printf("Digite o nome da categoria que você deseja listar:\n");
    scanf("%s", categoria);
    FILE* file = fopen("gastos.b", "rb");
    printf("nome, categoria, valor (em reais):\n");
    while(fread(&gasto, sizeof(gastos), 1, file)){
		    if(strcmp(gasto.categoria, categoria) == 0){
                printf("%s, %s, %f\n", gasto.nome, gasto.categoria, gasto.valor);
                valid = 1;
            }
        }
    if(valid == 0){
        printf("Não existe nenhum gasto dessa categoria!\n");
    }
    fclose(file);
}

struct Categorias{
    char categoria[20];
    float valor;
};

struct no2 {
    categorias dado;
    struct no2* prox;
};

struct lista2 {
    No2* inicio;
};

void adicionaFim2(Lista2 *lista2, categorias e) {
    No2* novo = (No2*) malloc(sizeof(No2));
    novo->dado = e;
    novo->prox = NULL;
    if (lista2->inicio == NULL) {
        lista2->inicio = novo;
    }
    else {
        No2* pi;
        for (pi = lista2->inicio; pi->prox != NULL; pi = pi->prox);
        pi->prox = novo;
    }
}

void liberarLista2(Lista2 *lista2) {
    No2 *atual = lista2->inicio;
    while (atual != NULL) {
        No2 *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista2->inicio = NULL;
}

void resumo(){
    int t = tamanho();
    int i = 0;
    Lista2 lista2;
    gastos gasto;
    int valid = 0;
    categorias categoriatemporario;
    strcpy(categoriatemporario.categoria, "");
    lista2.inicio = NULL;
    for(i = 0; i < t; i++){
        adicionaFim2(&lista2, categoriatemporario);
    }
    FILE* file = fopen("gastos.b", "rb");
    No2* pi2;
    No2* pi3;
    pi3 = lista2.inicio;
    while(fread(&gasto, sizeof(gastos), 1, file)){
        pi2 = lista2.inicio;
        for(i = 0; i < t; i++){
            if(strcmp(gasto.categoria, pi2->dado.categoria) == 0){
                valid = 1;
            }
            pi2 = pi2->prox;
        }
        if (valid == 0){
            strcpy(pi3->dado.categoria, gasto.categoria);
            pi3 = pi3->prox;
        }
        valid = 0;
    }
    fclose(file);
    for(pi3 = lista2.inicio; pi3 != NULL; pi3 = pi3->prox){
        pi3->dado.valor = 0;
    }
    file = fopen("gastos.b", "rb");
    while(fread(&gasto, sizeof(gastos), 1, file)){
        for(pi3 = lista2.inicio; pi3 != NULL; pi3 = pi3->prox){
            if(strcmp(gasto.categoria, pi3->dado.categoria) == 0){
                pi3->dado.valor = pi3->dado.valor + gasto.valor;
            }
        }
    }
    fclose(file);
    float gastototal = 0;
    printf("--- SEGUE O TOTAL GASTO POR CATEGORIA E O GASTO TOTAL ---\n");
    printf("--- TOTAL GASTO POR CATEGORIA ---\n");
    printf("categoria, gasto por categoria (em reais)\n");
    for(pi3 = lista2.inicio; pi3 != NULL; pi3 = pi3->prox){
        if(strcmp(pi3->dado.categoria, "") != 0){
            printf("%s, %f\n", pi3->dado.categoria, pi3->dado.valor);
        }
        gastototal = gastototal + pi3->dado.valor;
    }
    printf("\n--- GASTO TOTAL ---\n");
    printf("%f reais\n", gastototal);
    liberarLista2(&lista2);
}

void definirlimite(){
    FILE* file = fopen("limite.b", "wb");
    printf("Digite o limite dos gastos\n");
    float limite;
    scanf("%f", &limite);
    fwrite(&limite, sizeof(float), 1, file);
    printf("Limite de %f reais definido!\n", limite);
    fclose(file);
}

void gastoxlimite(){
    FILE* file = fopen("limite.b", "rb");
    float limite;
    fread(&limite, sizeof(float), 1, file);
    fclose(file);
    FILE* file2 = fopen("gastos.b", "rb");
    float gastototal = 0;
    gastos gasto;
    while(fread(&gasto, sizeof(gastos), 1, file)){
        gastototal = gastototal + gasto.valor;
    }
    float perc = (gastototal / limite) * 100;
    if (perc > 100){
        printf("Você já gastou %f reais, o que representa %f pontos percentuais do seu limite de %f reais e acabou passando dele\n", gastototal, perc, limite);
    }else{
        printf("Você já gastou %f reais, o que representa %f pontos percentuais do seu limite de %f reais e ainda não passou dele\n", gastototal, perc, limite);
    }
    fclose(file2);
}

void maiorparamenor(){
    FILE* file = fopen("gastos.b", "rb");
    gastos gasto;
    Lista lista;
    gastos temp;
    lista.inicio = NULL;
    while (fread(&gasto, sizeof(gastos), 1, file)) {
        adicionaFim(&lista, gasto);
    }
    fclose(file);
    No* pi;
    No* pi2;
    for(pi = lista.inicio; pi != NULL; pi = pi->prox){
        for(pi2 = pi->prox; pi2 != NULL; pi2 = pi2->prox){
            if(pi2->dado.valor > pi->dado.valor){
                temp = pi2->dado;
                pi2->dado = pi->dado;
                pi->dado = temp;
            }
        }
    }
    printf("Segue os gastos ordenados do maior para o menor:\n");
    printf("nome, categoria, valor (em reais):\n");
    for(pi = lista.inicio; pi != NULL; pi = pi->prox){
        printf("%s, %s, %f\n", pi->dado.nome, pi->dado.categoria, pi->dado.valor);
    }
    liberarLista(&lista);
}

void iniciarnovamente(){
    printf("Você tem certeza que deseja excluir os gastos e iniciar novamente?\nDIGITE 1 PARA SIM E 0 PARA NÃO\n");
    int confirm;
    scanf("%d", &confirm);
    gastos gasto;
    if(confirm == 1){
        printf("----- GASTOS EXCLUIDOS, INICIE COM UM NOVO GASTO -----:\n");
        FILE* file = fopen("gastos.b", "wb");
        printf("\n--------------- CADASTRO DE GASTO ---------------\n");   
        printf("informe o nome\n");
        scanf("%s", gasto.nome);
        printf("informe a categoria\n");
        scanf("%s", gasto.categoria);
        printf("informe o valor\n");
        scanf("%f", &gasto.valor);
        fwrite(&gasto, sizeof(gastos), 1, file);
        fclose(file);
    }else{
        printf("Voltando para o menu incial...");
    }
}