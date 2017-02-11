#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
int i, j;

void alocar_mapa(MAPA *m) {
	m->mapa = malloc(sizeof(char*) * m->linhas);
	for(i=0; i<(m->linhas); i++){
		m->mapa[i] = malloc(sizeof(char) * (m->colunas+1));
	}
}

void desalocar_mapa(MAPA *m){
	for(i=0; i<(m->linhas); i++){
		free(m->mapa[i]);
	}
	free(m->mapa);
}

void copiar_mapa(MAPA *destino, MAPA *origem){
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;

	alocar_mapa(destino);
	for(i=0; i<(origem->linhas); i++){
		strcpy(destino->mapa[i], origem->mapa[i]);
	}
}

void ler_mapa(MAPA *m){
	FILE *arq;

	arq = fopen("mapa.txt", "r");
	if(arq == 0){
		printf("Erro na leitura do arquivo!\n");
		exit(1);
	}

	fscanf(arq, "%d %d", &(m->linhas), &(m->colunas));

	alocar_mapa(m);

	for(i=0; i<(m->linhas); i++){
		fscanf(arq, "%s", m->mapa[i]);
	}

	fclose(arq);
}

int encontrar_no_mapa(MAPA *m, POSICAO *p, char c) {
	for(i=0; i<(m->linhas); i++){
		for(j=0; j<(m->colunas); j++){
			if(m->mapa[i][j] == c){
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}
	return 0;
}

int ehvalida(MAPA* m, int x, int y) {
	if(x >= m->linhas) 
		return 0;
	if(y >= m->colunas) 
		return 0;

	return 1;	
}

int ehparede(MAPA* m, int x, int y) {
	return 
		m->mapa[x][y] == PAREDE_VERTICAL ||
		m->mapa[x][y] == PAREDE_HORIZONTAL;
}

int ehpersonagem(MAPA* m, char personagem, int x, int y) {
	return
		m->mapa[x][y] == personagem;
}

int pode_andar(MAPA* m, char personagem, int x, int y) {
	return 
		ehvalida(m, x, y) && 
		!ehparede(m, x, y) &&
		!ehpersonagem(m, personagem, x, y);
}

void andar_no_mapa(MAPA *m, int Xorigem, int Yorigem, int Xdestino, int Ydestino) {
	char personagem = m->mapa[Xorigem][Yorigem];
	m->mapa[Xdestino][Ydestino] = personagem;
	m->mapa[Xorigem][Yorigem] = VAZIO;
}

void atualizar_posicao_do_pacman(POSICAO *p, int x, int y) {
	p->x = x;
	p->y = y;
}