#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int valor;

int conjectura(int dado){
    pid_t pid;
    
    pid = fork();
    if(pid == 0){//Processo filho
        while(dado != 1){//Condição até o fim, como descrito no enunciado
            printf("%d\n", dado);
            if(dado%2 == 0){//Se for par
                dado = dado/2;
            }
            else{
                dado = 3*dado+1;
            }
        }
        printf("%d\n", dado);
    }
    else
        //wait(null); Esse comando todas as vezes que executo dá erro
    return 0;
}

int main(){
    printf("INFORME UM VALOR:  ");
    scanf("%d", &valor);
    if(valor >= 1)//Condição para numeros válidos
        conjectura(valor);
    else
        printf("Entre com um valor válido");
    return 0;
}
