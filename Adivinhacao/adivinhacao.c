#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void abertura() {
	printf("\n\n");
	printf("          P  /_\\  P                              \n");
	printf("         /_\\_|_|_/_\\                            \n");
	printf("     n_n | ||. .|| | n_n         Bem vindo ao     \n");
	printf("     |_|_|nnnn nnnn|_|_|     Jogo de Adivinhação! \n");
	printf("    |\" \"  |  |_|  |\"  \" |                     \n");
	printf("    |_____| ' _ ' |_____|                         \n");
	printf("          \\__|_|__/                              \n");
	printf("\n\n");
}

int dificuldade() {
	int nivel = 0;
	int numero_de_tentativas = 0;

	printf("Qual o nível de dificuldade você deseja?\n");
	while(nivel > 3 || nivel == 0){
		printf("(1) = Facil, (2) = Médio, (3) = Difícil\n");
		printf("Nivel: ");
		scanf("%d", &nivel);

		switch(nivel){
			case 1:
				printf("Você escolheu o nivel facil, tem 20 tentativas para descobrir o número entre 1 e 500!\n");
				printf("Que o jogos comecem!\n\n");
				return numero_de_tentativas = 20;
			case 2:
				printf("Você escolheu o nivel Médio, tem 10 tentativas para descobrir o número entre 1 e 500!\n");
				printf("Que o jogos comecem!\n\n");
				return numero_de_tentativas = 10;
			case 3:
				printf("Você escolheu o nivel Dificil, tem 5 tentativas para descobrir o número entre 1 e 500!\n");
				printf("Que o jogos comecem!\n\n");
				return numero_de_tentativas = 5;
			default:
				printf("Por favor escolha as alternativas listadas!\n");
		}
	}
	return 0;
}

void tentativas() {

}

void resultado(int acertou, double pontos) {
	printf("Fim de jogo!\n");

	printf("\n");
	if(acertou) {
	    printf("             OOOOOOOOOOO               \n");
	    printf("         OOOOOOOOOOOOOOOOOOO           \n");
	    printf("      OOOOOO  OOOOOOOOO  OOOOOO        \n");
	    printf("    OOOOOO      OOOOO      OOOOOO      \n");
	    printf("  OOOOOOOO  #   OOOOO  #   OOOOOOOO    \n");
	    printf(" OOOOOOOOOO    OOOOOOO    OOOOOOOOOO   \n");
	    printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  \n");
	    printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  \n");
	    printf("OOOO  OOOOOOOOOOOOOOOOOOOOOOOOO  OOOO  \n");
	    printf(" OOOO  OOOOOOOOOOOOOOOOOOOOOOO  OOOO   \n");
	    printf("  OOOO   OOOOOOOOOOOOOOOOOOOO  OOOO    \n");
	    printf("    OOOOO   OOOOOOOOOOOOOOO   OOOO     \n");
	    printf("      OOOOOO   OOOOOOOOO   OOOOOO      \n");
	    printf("         OOOOOO         OOOOOO         \n");
	    printf("             OOOOOOOOOOOO              \n");
	    printf("\nParabéns! Você acertou!\n");
	    printf("Você fez %.2f pontos. Até a próxima!\n\n", pontos);
	} else {
	    printf("       \\|/ ____ \\|/    \n");
	    printf("        @~/ ,. \\~@      \n");
	    printf("       /_( \\__/ )_\\    \n");
	    printf("          \\__U_/        \n");
	    printf("\nVocê perdeu! Tente novamente!\n\n");
	}
}

int verificar_resultado(int chute, int numero_secreto) {
	int acertou = (chute == numero_secreto);
	int maior = (chute > numero_secreto);

	if(acertou){
		return 1;
	}else if(maior){
		printf("Errou! Seu chute foi maior que o número secreto!\n");
		return 0;
	}else{
		printf("Errou! Seu chute foi menor que  o número secreto!\n");
		return 0;
	}
}

int pontos_acumulados(int chute, int numero_secreto) {
	double pontos = 1000;
	double pontos_perdidos = abs(chute - numero_secreto)/(double)2;
	pontos -= pontos_perdidos;
	return pontos;
}

int sortear_numero() {
	int semente = time(0);
	int numero_secreto;

	srand(semente);
	numero_secreto = rand()%500 + 1;

	return numero_secreto;
}

int main() {

	int numero_secreto;
	int chute, ganhou, i;
	int tentativas = 0;
	int numero_de_tentativas;
	double pontos = 1000;

	void abertura();

	numero_secreto = sortear_numero();
	numero_de_tentativas = dificuldade();

	for(i=1; i<=numero_de_tentativas; i++){
		printf("Tentativa %d\n", tentativas+1);
		printf("Qual é o seu chute: ");
		scanf("%d", &chute);

		if(chute < 0){
			printf("Você não pode chutar números negativos!\n");
			continue;
		}

		ganhou = verificar_resultado(chute, numero_secreto);

		if(ganhou){
			break;
		}

		tentativas++;

		pontos = pontos_acumulados(chute, numero_secreto);
	}

	resultado(ganhou, pontos);

	return 0;
}
