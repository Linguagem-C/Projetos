#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define FANTASMA '<'
#define PILULA '*'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'

struct matriz_mapa {
	int linhas; 
	int colunas;
	char **mapa;
};

struct posicao {
	int x;
	int y;
};

typedef struct matriz_mapa MAPA;
typedef struct posicao POSICAO;


void alocar_mapa(MAPA *m);
void desalocar_mapa(MAPA *m);
void copiar_mapa(MAPA *destino, MAPA *origem);
void ler_mapa(MAPA *m);
int encontrar_no_mapa(MAPA *m, POSICAO *p, char c);
int ehvalida(MAPA* m, int x, int y);
int ehparede(MAPA* m, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);
int pode_andar(MAPA* m, char personagem, int x, int y);
void andar_no_mapa(MAPA *m, int Xorigem, int Yorigem, int Xdestino, int Ydestino);
void atualizar_posicao_do_pacman(POSICAO *p, int x, int y);

#endif