#include<stdio.h>
#include<stdlib.h>
#include <string.h>

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

void criaArquivo(){
	if(verificarArquivo()){
		return;
	}
	FILE *file;
	int i;
	
	Registro reg;
	/*reg.idade = 0;
	reg.chave = 0;*/
	reg.flag = 0;
	/*strcpy(reg.nome, "ninguem");*/

	file = fopen("arquivo.bin", "ab+");
	if(file != NULL){
		for(i=0; i<TAMANHO_ARQUIVOMAX; i++){
			// fseek(file, sizeof(Registro) *i, SEEK_SET);
			fwrite(&reg, sizeof(Registro), 1, file);
		}
	}
	/*int teste=5;
	file = fopen("arquivo.bin", "ab+");
	for(i=1; i<=TAMANHO_ARQUIVOMAX; i++){
			fseek(file, sizeof(int) *i, SEEK_SET);
			fwrite(&teste, sizeof(int), 1, file);
	}*/
		
	fclose(file);
}

void insereRegistro(Registro reg){
	FILE *file;
	Registro aux;
	int indice = 0;
	file = fopen("arquivo.bin", "rb+");
	fseek(file, 0, SEEK_SET);
	while(indice < TAMANHO_ARQUIVOMAX){
		fread(&aux, sizeof(Registro), 1, file);
		printf("%d\n", reg.flag);
		if(aux.flag != 1){
			fwrite(&reg, sizeof(Registro), 1, file);
			printf("Inserido com sucesso\n");
			return;
		}else{
			indice++;
			fseek(file, sizeof(Registro) * indice, SEEK_SET);
		}
	}
	printf("Erro na insercao: arquivo cheio\n");
	fclose(file);
}

void printAll(){
	Registro aux;
	FILE *f;
	int indice = 0;
	f = fopen("arquivo.bin", "rb");
	fseek(f, 0, SEEK_SET);
	for(int i=0; i<TAMANHO_ARQUIVOMAX; i++){
		fread(&aux, sizeof(Registro), 1, f);
		if(aux.flag == 0){
			printf("Nunca teve registro\n");
		}else if(aux.flag == 2){
			printf("Registro apagado\n");
		} else{
			printf("%d %s %d\n", aux.chave, aux.nome, aux.idade);
		}
		indice++;
		fseek(f, sizeof(Registro) * indice, SEEK_SET);
	}
	fclose(f);
}

int main(){

	if(verificarArquivo()){
		printf( "Existe\n" );
	}else{
		printf("Não existe\n");
	}

	criaArquivo();

	Registro teste;

	teste.chave = 33;
	teste.idade = 69;
	teste.flag = 1;
	strcpy(teste.nome, "ahsdjhakdh");

	insereRegistro(teste);

	printAll();





}