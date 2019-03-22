
/*	Trabalho prático 1 - MATA54
	Alunos:
	Eric dos Santos Sampaio
	Gregory Silva Gley Santos
	Lucas Natanael Brito Prates
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAMANHO_ARQUIVOMAX 11 
#define TAMANHO_NOME 21

typedef struct registro{
	int chave;
	int idade;
	char nome[TAMANHO_NOME];
	int flag;
	/* flag = 0 nunca teve nada
	   flag = 1 tem um registro
	   flag = 2 tinha registro, mas foi apagado
	*/
} Registro;

/*	verifica se "arquivo.bin" já existe, se sim
	retorna 1, caso contrário retorna 0 
*/
int verificarArquivo(){
	FILE *check;
	check = fopen("arquivo.bin", "rb");
	if(check == NULL){
		return 0;
	} else {
		fclose(check);
		return 1;
	}
}

/* 	cria "arquivo.bin", caso ainda não exista,
	e escreve no arquivo um vetor de struct do tipo
	Registro
*/
void criarArquivo(Registro reg[TAMANHO_ARQUIVOMAX]){
	if(verificarArquivo()){
		return;
	}
	FILE *file;
	int i;
	
	file = fopen("arquivo.bin", "ab+");
	if(file != NULL){
		for(i=0; i<TAMANHO_ARQUIVOMAX; i++){		
			fwrite(&reg[i], sizeof(Registro), 1, file);
		}
	}		
	fclose(file);
}

/* 	verifica se determinada chave se encontra
	no arquivo, retorna 1 se encontrar, retorna 0
	caso contrário
*/
int checkIfKeyExists(int key, FILE *file){
	Registro aux;
	for(int i=0; i<TAMANHO_ARQUIVOMAX; i++){
		fseek(file, sizeof(Registro)*i, SEEK_SET);
		fread(&aux, sizeof(Registro), 1, file);
		if(aux.flag == 1 && aux.chave == key){
			return 1;
		}
	}
	return 0;
}

/* 	insere registro no arquivo caso a chave nao
	exista no mesmo, e se existir alguma posicao vazia
	(com valor de flag 0 ou 2)
*/
void insereRegistro(Registro reg){
	FILE *file;
	Registro aux;
	int indice = 0;
	file = fopen("arquivo.bin", "rb+");
	if(checkIfKeyExists(reg.chave, file)){
		printf("registro com chave existente\n");
		fclose(file);
		return;
	}
	while(indice < TAMANHO_ARQUIVOMAX){
		fseek(file, sizeof(Registro)*indice, SEEK_SET);
		fread(&aux, sizeof(Registro), 1, file);
		if(aux.flag != 1){
			reg.flag = 1;
			fseek(file, sizeof(Registro)*indice, SEEK_SET);
			fwrite(&reg, sizeof(Registro), 1, file);
			fclose(file);
			return;
		}else{
			indice++;
		}
	}
	fclose(file);
}

/* 	imprime um unico registro
*/
void printSingle(Registro reg){
	printf("chave: %d %s %d\n", reg.chave, reg.nome, reg.idade);
}

/* 	procura no arquivo o registro com a chave dada
	e imprime os valores, caso a chave seja encontrada
*/
void consultaRegistro(int chave){
	FILE *file;
	Registro aux;
	file = fopen("arquivo.bin", "rb");
	for(int i=0; i<TAMANHO_ARQUIVOMAX; i++){
		fseek(file, sizeof(Registro) * i, SEEK_SET);
		fread(&aux, sizeof(Registro), 1, file);
		if(aux.flag == 1 && aux.chave == chave){
			printSingle(aux);
			fclose(file);
			return;
		}
	}
	printf("nao ha registro com chave: %d\n", chave);
	fclose(file);
}

/* 	"remove" o registro com a chave dada do arquivo,
	mudando o seu valor de flag para 2
*/
void removeRegistro(int chave){
	FILE *file;
	Registro aux;
	file = fopen("arquivo.bin", "rb+");
	for(int i=0; i<TAMANHO_ARQUIVOMAX; i++){
		fseek(file, sizeof(Registro) * i, SEEK_SET);
		fread(&aux, sizeof(Registro), 1, file);
		if(aux.flag == 1 && aux.chave == chave){
			aux.flag = 2;
			fseek(file, sizeof(Registro) *i, SEEK_SET);
			fwrite(&aux, sizeof(Registro), 1, file);
			fclose(file);
			return;
		}
	}
	printf("nao existe registro com chave: %d\n", chave);
	fclose(file);
}

/* 	imprime todos os registros, no formato:
	posicao que se encontra no arquivo - chave - nome - idade
*/
void printAll(){
	Registro aux;
	FILE *file;
	file = fopen("arquivo.bin", "rb");
	for(int i=0; i<TAMANHO_ARQUIVOMAX; i++){
		fseek(file, sizeof(Registro) * i, SEEK_SET);
		fread(&aux, sizeof(Registro), 1, file);
		if(aux.flag == 1){
			printf("posicao: %d ", i);
			printSingle(aux);
		}else {
			printf("posicao: %d ", i);
			printf("vazia\n");
		} 
	}
	fclose(file);
}

int main(){

	Registro registro[TAMANHO_ARQUIVOMAX];
	for(int i=0; i<TAMANHO_ARQUIVOMAX; i++){
		registro[i].flag = 0;
	}

	criarArquivo(registro);

	Registro reg;
	char opcao;
	int chave;

	while(1){
		scanf("%c", &opcao);
		if(opcao == 'e') break;
		switch(opcao){
			case 'i':
				fflush(stdin);
				scanf("%d", &reg.chave);
				fflush(stdin);
				char buffer[21];
				fgets (buffer, sizeof(buffer), stdin);
				if(buffer[strlen(buffer)-1] == '\n'){
					buffer[strlen(buffer)-1] = '\0';
				}
				strcpy(reg.nome, buffer);
				scanf("%d", &reg.idade);
				insereRegistro(reg);
			break;
			case 'c':
				scanf("%d", &chave);
				consultaRegistro(chave);
			break;
			case 'r':
				scanf("%d", &chave);
				removeRegistro(chave);
			break;
			case 'p':
				printAll();
			break;
			default:
				break;
		}
	}

}