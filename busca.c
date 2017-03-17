#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	pid_t pid;
	int x, y, inicio, fim, limite;
	FILE *fp;
	char line[13], recebe[0];
	size_t len = 0;
    size_t read;

    fp = fopen("busca.txt", "r");
	if (fp == NULL){
		return 0;
	}

	while (fgets(line, 12, fp)!= NULL) {
		printf("%s", line);
	}
		
	limite =  len/4;
	inicio = 0;
	fim = limite;
	printf("Início %d \n", inicio);
	printf("Fim %d \n", fim);
	printf("Limite %d \n", limite);

	int ab = 0;
	for(x = 0; x < 4; x++){
		pid = fork();
		if(pid == 0){
			for(y = inicio; y < fim; y++){
				if(ab == 0){
					printf("OI\n");
				}
			}
		}
	}
	
	inicio = fim;
	fim += limite;

	fclose(fp);
	exit(EXIT_SUCCESS);
		
}


	
