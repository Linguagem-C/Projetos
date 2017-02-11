#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

char desenharParede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenharFantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenharHeroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenharPilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenharVazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimir_parte(char desenho[4][7], int parte) {
	printf("%s", desenho[parte]);
}

void imprimir_mapa(MAPA *m){
	int i, j, parte;
	for(i=0; i<(m->linhas); i++){

		for(parte = 0; parte < 4; parte++){

			for(j=0; j<(m->colunas); j++){

				switch(m->mapa[i][j]){
					case FANTASMA:
						imprimir_parte(desenharFantasma, parte);
						break;

					case HEROI:
						imprimir_parte(desenharHeroi, parte);
						break;

					case PILULA:
						imprimir_parte(desenharPilula, parte);
						break;

					case PAREDE_VERTICAL:
					case PAREDE_HORIZONTAL:
						imprimir_parte(desenharParede, parte);
						break;

					case VAZIO:
						imprimir_parte(desenharVazio, parte);
						break;

				}
			}
			printf("\n");
		}
	}
}