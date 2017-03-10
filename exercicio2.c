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
	char line[13], recebe[1];
	size_t len = 0;
    	size_t read;

    	fp = fopen("exercicio2.txt", "r");
	if (fp == NULL){
		return 0;
	}

	while (fgets(line, 12, fp)!= NULL) {
		printf("%s", line);
	}
		
	recebe = line[2];		
	printf("Testando %c", recebe);

	limite =  len/4;
	inicio = 0;
	fim = limite;
	
	for(x = 0; x < 4; x++){
		pid = fork();
		if(pid == 0){
			for(y = inicio; y < fim; y++){
				if(line[y] == recebe){
					
				}
			}
		}
	}
	
	inicio = fim;
	fim += limite;

	fclose(fp);
	exit(EXIT_SUCCESS);
		
}


	
