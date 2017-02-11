#include "lib/bagofword.h"

int main(){

  int qtd=0, quantidadePalavras=0;
  char palavra[30];

  BagOfWords *palavras;

  palavras = alocar_memoria();

  qtd = ler_arquivo (&quantidadePalavras, palavra, palavras);

  ordenar(qtd, palavras);

  return 0;
}
