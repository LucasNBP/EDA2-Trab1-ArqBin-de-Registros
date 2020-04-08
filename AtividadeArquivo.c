
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAMANHO_ARQUIVO 11
FILE *arq;

typedef struct {
	int chave;
	int idade;
	char nome[20];
}pessoa;

void inicializa(){
	pessoa x;
	x.chave=-1;
	for(int i=0;i< TAMANHO_ARQUIVO;i++)
		fwrite(&x,sizeof(pessoa),1, arq);
}

void posicionaApontadorArquivo(int indice){
	rewind (arq); // apontador para o inicio do arquivo	
	fseek ( arq , sizeof(pessoa)*indice , SEEK_SET ); //move o apontador do aquivo para a posi. da variavel

}
	
void insere(){
	int indice=0;
	pessoa x, y;
	scanf("%d",&x.chave);
	scanf("%s",x.nome);
	scanf("%d",&x.idade);
	scanf("%d",&indice);
	
	posicionaApontadorArquivo(indice);
	
	fread(&y, sizeof(pessoa), 1	, arq);
	if(y.chave != -1){
		printf("posicao ocupada: %d\n", indice);
		return;
	}
	
	posicionaApontadorArquivo(indice);
	
	fwrite(&x,sizeof(pessoa),1, arq);	
}

void consulta(){
	int indice=0;
	pessoa x;
	scanf("%d",&indice);
	
	posicionaApontadorArquivo(indice);
	
	fread(&x, sizeof(pessoa), 1	, arq);
	if(x.chave != -1){
		printf("chave: %d %s %d\n",x.chave,x.nome,x.idade);
	}else{
		printf("posicao vazia: %d", indice);
	}
}

void remove(){
	int indice=0;
	pessoa x,y;
	scanf("%d",&indice);
	
	posicionaApontadorArquivo(indice);
	
	fread(&y, sizeof(pessoa), 1	, arq);
	if(y.chave != -1){
		
		posicionaApontadorArquivo(indice);
		
		x.chave=-1;
		fwrite(&x,sizeof(pessoa),1, arq);
	}else{
		printf("posicao ja estava vazia: %d", indice);
	}
}
void imprime(){
	pessoa x;
	for(int i=0;i< TAMANHO_ARQUIVO;i++){
		fread(&x,sizeof(pessoa),1, arq);
		if(x.chave != -1){
			printf("%d: %d %s %d\n", i, x.chave, x.nome, x.idade);
		}else{
			printf("%d: vazio\n", i);
		}
	}
}	
int main(int argc, char **argv)
{
	char c;
	if (!(arq = fopen("arquivo", "r")))
    {
		arq=fopen("arquivo","a");
		inicializa();
		fclose(arq);
	}
	
	while(1==1){
		scanf("%c",&c);
		switch (c){
			case 'i':
			//chamar a funcao inserir
				arq=fopen("arquivo","r+");
				insere();
				fclose(arq);
				//printf("Fim insert\n");
			break;
			
			case 'c':
			//chamar a funcao consulta
				arq=fopen("arquivo","r+");
				consulta();
				fclose(arq);
			break;
			
			case 'r':
			//chamar a funcao remove
				arq=fopen("arquivo","r+");
				remove();
				fclose(arq);
			break;
			case 'p':
			//chamar a funcao imprime
				arq=fopen("arquivo","r+");
				imprime();
				fclose(arq);
				
			break;
			case 'e':
				exit(1);
			break;
			}
	}

	return 0;
}

