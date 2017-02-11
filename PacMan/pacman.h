#ifndef _PACMAN_H_
#define _PACMAN_H_

#define DIREITA 'd'
#define ESQUERDA 'a'
#define CIMA 'w'
#define BAIXO 's'
#define BOMBA 'b'

int tecla_errada(char direcao);
void mover(char direcao);
void fantasmas();
void opcoes_de_posicao(int opcoes[][2], int Xatual, int Yatual);
int sortear_posicao_fantasma();
int pra_onde_vai_o_fantasma(int Xatual, int Yatual, int *Xdestino, int *Ydestino);
void explode_pilula();
void metodo_explode_pilula(int x, int y, int somaX, int somaY, int qtd);
int acabou();

#endif

/*
	- Concertar o movimento do fantasma, colocar um laço para sortear várias vezes até que fantasma ande
	- Colocar leveis e novos mapas

*/