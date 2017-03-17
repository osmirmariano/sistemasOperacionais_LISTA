#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
	pid_t pid;
	int i, j, inicio, fim, sizeVetor, limite, tamLeitura;
	char *novo, vetor[27], pesquisar;
	FILE *arq;

	tamLeitura = 27;

	//Trecho onde o usuário irá informar o elemento que deseja buscar
	printf("INFORME O ELEMENTO QUE DESEJA PESQUISAR: ");
	fflush(stdin);
	scanf("%c", &pesquisar);
	fflush(stdin);
	// Abre um arquivo texto para leitura
	arq = fopen("busca.txt", "rt");
	//verifica se o arquivo abriu com sucesso
	if(arq == NULL) {
		printf("Abriu arquivo");
		return 0;
	}
	//variável novo vai receber todos os dados presente no arquivo de texto
	novo = fgets(vetor, tamLeitura, arq);

	if(novo){
		sizeVetor = strlen(vetor);
		limite = sizeVetor/5;
		inicio = 0;
		fim = limite;
		
		int i, j;
		for (i = 0; i < limite; i = i + 1){
			pid = fork();
			//Condição verifica se é processo filho
			if (pid == 0){
				//Laço para procurar nosso elemento informado pelo usuário
				for (j = inicio; j < fim; j = j + 1){
					if(vetor[j] == pesquisar){
						printf("\n ELEMENTO %c ENCONTRADO - PROCESSO %d \n \n", pesquisar, getpid());
					}
				}
				exit(0);
			}
			inicio = fim;
			fim = fim + limite;
			if(fim == 25)
				fim = fim+1;
		}
	}
	return 0;
}
