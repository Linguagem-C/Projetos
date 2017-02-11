#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  char palavra[30];
  int quantidade;
} BagOfWords;

BagOfWords *alocar_memoria();
void compara_palavra(int *qtd, char *palavra, int *quantidadePalavras, BagOfWords *palavras);
int ler_arquivo(int *quantidadePalavras, char *palavra, BagOfWords *palavras);
void bagofwords(int qtd, int quantidadePalavras, BagOfWords *palavras);
void ordenar(int qtd, BagOfWords *palavras);
