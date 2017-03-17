#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 /* Definindo o tamanho máximo do comando */
#define TAM 50
#define buffer "\nHistórico de comando do Shell"

char historico[6][TAM]; //Uma matriz de char para armazenar o histórico
int cont = 0; //Contador

/*-----------------------------------FUNÇÃO PRINCIPAL----------------------------------*/
int main(){
    char armazenaEntrada[MAX_LINE]; /*Para armazenar a entrada do comando*/
    char *args[MAX_LINE/2+1]; /*Definindo a quantidade de argumentos máximos */
    int should_run = 1, flag; //a flag para fazer tratamento quando for igual a 1 se o comando é seguido por "&"
 
    pid_t pid,tpid;
    int i;
   
    while (should_run){ //Esse while com o paramentro should_run cria um loop infinito para o Shell até que o usuário pressione Ctrl+C para sair      
        flag = 0; //flag = 0 por padrão
        printf("meuShell>");
        fflush(stdout);
        if(-1 != comandosShell(armazenaEntrada, args, &flag)){ // condição para obter o próximo comando  
		    pid = fork();   
        	if (pid < 0){
            	printf("Fork deu erro.\n");
            	exit (1);
        	}
       		else if (pid == 0){
           	    //Caso o usuário informe algum comando que não existe
            	if (execvp(args[0], args) == -1){	
                	printf("Erro ao executar o comando\n");
            	}
       		}
            //Nesse caso se a flag == 0, o pai vai esperar. Caso contrário chama a função  comandosShell
        	else{
            	i++;
           	 	if (flag == 0){
                	i++;
                	//wait(NULL);
           		 }
        	}
   	    }
     }
}



/*-------------------------------FUNÇÃO QUE IRÁ EXIBIR O HISTÓRICO DO SHELL----------------------------------*/
void historicoShell(){
    int i, j = 0, contHist = cont;
    
    printf("Histórico do Shell:\n");
    for (i = 0; i < 6; i++){ //laço de repetição para interar entre os comandos
        printf("%d -  ", contHist);
        while (historico[i][j] != '\n' && historico[i][j] != '\0') {	
            printf("%c", historico[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        contHist--;
        if (contHist ==  0)
            break;
    }
    printf("\n");
} 

/*--------------------FUNÇÃO UTILIZADA PARA PEGAR OS COMANDOS DO SHELL E TRAMENTO DO HISTÓRICO--------------------*/
//Essa função é utilizada para pegar os comandos do Shell
int comandosShell(char texto[], char *args[], int *flag){
   	int i, tamanho; //Para caracteres na linha de comando
    int inicio;  //indice do início do próximo comando
    int ct = 0; // indice de onde colocar o próximo parâmetro args[]

    tamanho = read(STDIN_FILENO, texto, MAX_LINE);//tamanho recebe a quantidade de dados lido pela função read
    inicio = -1;

    if (tamanho == 0)
        exit(0);   //Finaliza o comando
    if (tamanho < 0){
        printf("Não foi possível ler o comando\n");
        exit(-1);  //Encerra a execução
    }
    
   //Examina cada caracter inserido
    for (i = 0; i < tamanho; i++){
        switch (texto[i]){
            case ' ':
            case '\t' : // Para separar os argumentos
                if(inicio != -1){
                    args[ct] = &texto[inicio];    
                    ct++;
                }
                texto[i] = '\0'; //Adicionar um caractere nulo no final
                inicio = -1;
                break;
                
            case '\n': //final char 
                if (inicio != -1){
                    args[ct] = &texto[inicio];
                    ct++;
                }
                texto[i] = '\0';
                args[ct] = NULL;
                break;
                
            default :           
                if (inicio == -1)
                    inicio = i;
                if (texto[i] == '&'){
                    *flag  = 1; //A flag diferencia se o o processo filho é invocado em Background
                    texto[i] = '\0';
                }
        }
    }
    
    args[ct] = NULL; //Se a linha de entrada for > 80

    //Código abaixo todo se refere ao tramento do histório. Poderia criar uma outra função para essa, mas vamos ficar assim mesmo.
    //Condição para chamar a função histórico e demais questões relacionado a ele
    if(strcmp(args[0],"historico")==0){		
        if(cont > 0){
            historicoShell();
	    }
		else{
		    printf("\nNão existe comandos no histórico\n");
		}
		return -1;
    }
	else if (args[0][0]-'!' == 0){	
        int x = args[0][1]- '0'; 
		int z = args[0][2]- '0'; 
		
		if(x > cont) { 
		    printf("\nNão existe esse comando no histórico\n");
		    strcpy(texto,"Comando Errado");
		} 
		else if (z != -48){
		    printf("\nO comando do histórico. Digite < =! 5 (tamanho do buffer é 6 junto com o comando atual)\n");
		    strcpy(texto,"Comando Errado");
		}
		else{
			if(x ==- 15){//Verificando o valor de "!!" na tabela ASCII é 33.
				 strcpy(texto,historico[0]); 
			}
			else if(x == 0){
				 printf("Insira o comando adequado");
				strcpy(texto,"Comando Errado");
			}
			
			else if(x >= 1){
				strcpy(texto,historico[cont-x]);
			}
		}
	}
    //for para mover os elementos do histórico
    for (i = 9; i > 0; i--)
       	strcpy(historico[i], historico[i-1]);
    
    strcpy(historico[0], texto); // Atualiza a matriz de histórico com os dados de entrada
    cont++;
	if(cont > 10)	{ 
        cont = 10;
	}
}
