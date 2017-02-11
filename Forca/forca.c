#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "forca.h"
#define TAM 20

char palavra_secreta[TAM];
char chutes[26];
int chutes_dados = 0;
int i, j;

int main() {
	
	char jogar_novamente;
	int nao_acertar_e_nao_inforcar;

	abertura();

	do{
		escolher_palavra();
		chutes_dados = 0;
		do {
			system("clear");
			forca();

			chutar(&chutes_dados);

			nao_acertar_e_nao_inforcar = !acertou() && !enforcou();

		}while(nao_acertar_e_nao_inforcar);

		jogar_novamente = resultado();

	}while(jogar_novamente == 'S');

	adicionar_palavra();

	return 0;
}

void abertura(){
	printf("\n\n");
	printf("*******************************\n");
	printf("**       Jogo da Forca       **\n");
	printf("*******************************\n\n");
}

void escolher_palavra() {
	FILE *arquivo;
	int palavra_aleatorio;
	int quantidade_de_palavras;

	/* Abre o arquivo forca.txt no modo de leitura */
	arquivo = fopen("forca.txt", "r");

	/* Verificar se o arquivo existe, caso não exista finalize o programa. */
	if(arquivo == 0){
		printf("Desculpe, banco de dados não disponivel!\n\n");
		exit(1);
	}

	/* Irá ler a primeiro linha do arquivo forca.txt que é a quantidade de palavras do arquivo */
	fscanf(arquivo, "%d", &quantidade_de_palavras);

	/* Sorteia uma palavra aleatoriamente de 0 até a quantidade de palavras */
	srand(time(0));
	palavra_aleatorio = rand() % quantidade_de_palavras;

	/* Percorrer as palavras */
	for(i=0; i<=palavra_aleatorio; i++){
		fscanf(arquivo, "%s", 	palavra_secreta);
	}

	/* Fecha o arquivo */
	fclose(arquivo);
}

void chutar(int *chutes_dados){
	char chute;
	printf("Insira uma letra: ");
	scanf(" %c", &chute);
	chute = toupper(chute);

	chutes[(*chutes_dados)] = chute;
	(*chutes_dados)++;
}


int verificar_chute(char letra) {
	int achou = 0;
	for(j=0; j<chutes_dados; j++){
		if (chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}


int chutes_errados(){
	int erros = 0;
	for(i=0; i<chutes_dados; i++){
		int existe = 0;
		int nao_encontrei;
		
		for(j=0; j<strlen(palavra_secreta); j++){
			int achou = (chutes[i] == palavra_secreta[j]);
			if(achou){
				existe = 1;
				break;
			}
		}

		nao_encontrei = !existe;
		if(nao_encontrei){
			erros++;
		}
	}
	return erros;
}

void desenhar_forca(){
	int errou = chutes_errados();
	printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c \n", (errou >= 1 ? '(' : ' '), 
    							(errou >= 1 ? '_' : ' '),
    							(errou >= 1 ? ')' : ' '));
    printf(" |      %c%c%c \n", (errou >= 3 ? '\\' : ' '), 
    							(errou >= 2 ? '|' : ' '), 
    							(errou >= 4 ? '/' : ' '));
    printf(" |       %c    \n", (errou >= 2 ? '|' : ' '));
    printf(" |      %c %c  \n", (errou >= 5 ? '/' : ' '), 
    							(errou >= 6 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");
}


int enforcou() {
	
	int erros = chutes_errados();
	
	return erros >= 7;
}


int acertou() {
	for(i = 0; i<strlen(palavra_secreta); i++){
		int nao_completou_palavra = !verificar_chute(palavra_secreta[i]);
		if(nao_completou_palavra)
			return 0;
	}
	return 1;
}


void forca() {

	desenhar_forca();

	for(i=0; i<strlen(palavra_secreta); i++){
		
		int achou = verificar_chute(palavra_secreta[i]);

		if(achou){
			printf("%c ", palavra_secreta[i]);
		}else{
			printf("_ ");
		}
	}
	printf("\n");
}

char resultado(){
	char jogar_novamente;
	int ganhou = acertou();

	if(ganhou){
		printf("\nParabéns, você ganhou!\n\n");
		printf("A palavra era **%s**\n\n", palavra_secreta);
	    printf("       ___________      \n");
	    printf("      '._==_==_=_.'     \n");
	    printf("      .-\\:      /-.    \n");
	    printf("     | (|:.     |) |    \n");
	    printf("      '-|:.     |-'     \n");
	    printf("        \\::.    /      \n");
	    printf("         '::. .'        \n");
	    printf("           ) (          \n");
	    printf("         _.' '._        \n");
	    printf("        '-------'       \n\n");
	}else{
		printf("\nGame Over!, você foi enforcado!\n");
	    printf("A palavra era **%s**\n\n", palavra_secreta);
	    printf("    _______________         \n");
	    printf("   /               \\       \n"); 
	    printf("  /                 \\      \n");
	    printf("//                   \\/\\  \n");
	    printf("\\|   XXXX     XXXX   | /   \n");
	    printf(" |   XXXX     XXXX   |/     \n");
	    printf(" |   XXX       XXX   |      \n");
	    printf(" |                   |      \n");
	    printf(" \\__      XXX      __/     \n");
	    printf("   |\\     XXX     /|       \n");
	    printf("   | |           | |        \n");
	    printf("   | I I I I I I I |        \n");
	    printf("   |  I I I I I I  |        \n");
	    printf("   \\_             _/       \n");
	    printf("     \\_         _/         \n");
	    printf("       \\_______/           \n");
	}

	printf("Deseja jogar novamente? (S/N)\n");
	scanf(" %c", &jogar_novamente);
	jogar_novamente = toupper(jogar_novamente);

	return jogar_novamente;
}


void adicionar_palavra(){
	char quero;
	char nova_palavra[20];
	int quantidade_de_palavras;
	FILE *arquivo;
	
	printf("Você deseja adicionar uma nova palavra ao jogo? (S/N)\n");
	scanf(" %c", &quero);
	quero = toupper(quero);

	if(quero == 'S'){

		printf("Qual a nova palavra: ");
		scanf("%s", nova_palavra);

		/* Colocar a palavra em letra maiuscula */
		for(i=0; i<strlen(nova_palavra); i++){
			nova_palavra[i] = toupper(nova_palavra[i]);
		}

		/* Abre o arquivo forca.txt no modo leitura e escrita */
		arquivo = fopen("forca.txt", "r+");

		/* Verificar se o arquivo existe, caso não exista finalize o programa. */
		if(arquivo == 0){
			printf("Desculpe, banco de dados não disponivel!\n\n");
			exit(1);
		}

		/* Pegar a quantidade de palavras do arquivo e somar mais 1 */
		fscanf(arquivo, "%d", &quantidade_de_palavras);
		quantidade_de_palavras++;

		/* Posicionar o ponteiro para o começo do arquivo novamente */
		fseek(arquivo, 0, SEEK_SET);

		/* Escrever no arquivo a quantidade de palavras */
		fprintf(arquivo, "%d", quantidade_de_palavras);

		/* Posicionar o ponteiro para o fim do arquivo */
		fseek(arquivo, 0, SEEK_END);

		/* Escrever a nova palavra no fim do arquivo */
		fprintf(arquivo,"\n%s", nova_palavra);

		/* Fechar arquivo */
		fclose(arquivo);
	}
}