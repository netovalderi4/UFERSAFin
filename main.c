#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UFERSAFin.h"

int main(){
    int oplogin = menulogin();
    while(oplogin != 0){
    	if (oplogin == 1){
            int b = login();
            if(b == 1){
                printf("--- LOGIN BEM SUCEDIDO ---\n");
                printf("----------------------------------- \nSeja bem vindo ao sistema de gerenciamente e controle financeiro UFERSAFin, aqui \nvocê pode registrar e acompanhar os seus gastos para um melhor controle das despesas!\n -----------------------------------\n");
                int opsistema = menusistema();
                while(opsistema != 0){
                    if(opsistema == 1){
                        cadastrar();
                        opsistema = menusistema();
                    }else if(opsistema == 2){
                        listar();
                        opsistema = menusistema();
                    }else if(opsistema == 3){
                        editar();
                        opsistema = menusistema();
                    }else if(opsistema == 4){
                        excluir();
                        opsistema = menusistema();
                    }else if(opsistema == 5){
                        buscar();
                        opsistema = menusistema();
                    }else if(opsistema == 6){
                        listarcategoria();
                        opsistema = menusistema();
                    }else if(opsistema == 7){
                        resumo();
                        opsistema = menusistema();
                    }else if(opsistema == 8){
                        definirlimite();
                        opsistema = menusistema();
                    }else if(opsistema == 9){
                        gastoxlimite();
                        opsistema = menusistema();
                    }else if(opsistema == 10){
                        maiorparamenor();
                        opsistema = menusistema();
                    }else if(opsistema == 11){
                        iniciarnovamente();
                        opsistema = menusistema();
                    }
                }
                oplogin = 0;
            }
            else if(b == 0){
                printf("--- LOGIN INVÁLIDO ---\n");
                oplogin = menulogin();
            }
            }
            else if(oplogin == 2){
                cadastrarusuario();
                oplogin = menulogin();
            }
        }
    }
