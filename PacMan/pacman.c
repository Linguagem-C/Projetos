#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "mapa.h"
#include "ui.h"

int i, j;
int tem_pilula = 0;
MAPA m;
POSICAO heroi;

int main(){

	char comando;

	ler_mapa(&m);
	encontrar_no_mapa(&m, &heroi, HEROI);
	
	do {
		system("clear");
		printf("Tem pilula: %s\n", (tem_pilula ? "SIM" : "NÃO"));
		imprimir_mapa(&m);

		printf("Comando: ");
		scanf(" %c", &comando);
		mover(comando);
		if(comando == BOMBA) explode_pilula();
		fantasmas();

	}while(!acabou());

	desalocar_mapa(&m);
	return 0;
}

int tecla_errada(char direcao){
	int teclaErrada = (direcao != ESQUERDA && direcao != DIREITA && direcao != CIMA && direcao != BAIXO);
	return teclaErrada;
}


void mover(char direcao) {

	int proximoX = heroi.x;
	int proximoY = heroi.y;

	if(tecla_errada(direcao)) return;

	switch(direcao){
		case ESQUERDA:
			proximoY--;
			break;
		case DIREITA:
			proximoY++;
			break;
		case CIMA:
			proximoX--;
			break;
		case BAIXO:
			proximoX++;
			break;	
	}

	if(!pode_andar(&m, HEROI, proximoX, proximoY)) return;

	if(ehpersonagem(&m, PILULA, proximoX, proximoY)){
		tem_pilula = 1;
	}

	if(ehpersonagem(&m, FANTASMA, proximoX, proximoY)){
		printf("Perdeu!\n");
		exit(0);
	}

	andar_no_mapa(&m, heroi.x, heroi.y, proximoX, proximoY);

	atualizar_posicao_do_pacman(&heroi, proximoX, proximoY);

}

int sortear_posicao_fantasma() {
	int posicao;

	srand(time(0));
	posicao = rand() % 4;

	return posicao;
}

void opcoes_de_posicao(int opcoes[][2], int Xatual, int Yatual) {

	int direita = Yatual+1;
	int esquerda = Yatual-1;
	int cima = Xatual-1;
	int baixo = Yatual-1;
	int Nao_mover_no_eixoX = Xatual;
	int Nao_mover_no_eixoY = Yatual;

	opcoes[0][0] = Nao_mover_no_eixoX;
	opcoes[0][1] = direita;
	opcoes[1][0] = baixo;
	opcoes[1][1] = Nao_mover_no_eixoY;
	opcoes[2][0] = Nao_mover_no_eixoX;
	opcoes[2][1] = esquerda;
	opcoes[3][0] = cima;
	opcoes[3][1] = Nao_mover_no_eixoY;

}

int pra_onde_vai_o_fantasma(int Xatual, int Yatual, int *Xdestino, int *Ydestino) {
	int posicao;
	int opcoes[4][2];

	opcoes_de_posicao(opcoes, Xatual, Yatual);

	posicao = sortear_posicao_fantasma();

	if(pode_andar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
		*Xdestino = opcoes[posicao][0];
		*Ydestino = opcoes[posicao][1];
		return 1;
	}

	return 0;
}

void fantasmas(){
	MAPA copia;
	int Xdestino, Ydestino, encontrou;
	copiar_mapa(&copia, &m);

	for(i=0; i<copia.linhas; i++){
		for(j=0; j<copia.colunas; j++){
			if(copia.mapa[i][j] == FANTASMA){

				encontrou = pra_onde_vai_o_fantasma(i, j, &Xdestino, &Ydestino);
				if(encontrou){
					andar_no_mapa(&m, i, j, Xdestino, Ydestino);
				}
				
			}
		}
	}
	desalocar_mapa(&copia);
}

void explode_pilula() {
	int direita = 1;
	int esquerda = -1;
	int cima = -1;
	int baixo = 1;
	int eixoX = 0;
	int eixoY = 0;
	int quantidade_de_casas = 3;

	if(!tem_pilula) return;

	metodo_explode_pilula(heroi.x, heroi.y, eixoX, direita, quantidade_de_casas);
	metodo_explode_pilula(heroi.x, heroi.y, eixoX, esquerda, quantidade_de_casas);
	metodo_explode_pilula(heroi.x, heroi.y, cima, eixoY, quantidade_de_casas);
	metodo_explode_pilula(heroi.x, heroi.y, baixo, eixoY, quantidade_de_casas);

	tem_pilula = 0;
}

void metodo_explode_pilula(int x, int y, int somaX, int somaY, int qtd) {

	int eixoX = x + somaX;
	int eixoY = y + somaY;

	if(qtd == 0) return;
	if(!ehvalida(&m, eixoX, eixoY)) return;
	if(ehparede(&m, eixoX, eixoY)) return;
	
	m.mapa[eixoX][eixoY] = VAZIO;

	metodo_explode_pilula(eixoX, eixoY, somaX, somaY, qtd-1);


}

int acabou() {
	POSICAO nula;
	int perdeu = !encontrar_no_mapa(&m, &nula, HEROI);
	int ganhou = !encontrar_no_mapa(&m, &nula, FANTASMA);

	return ganhou || perdeu;
}