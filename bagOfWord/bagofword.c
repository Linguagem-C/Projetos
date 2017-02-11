#include "lib/bagofword.h"

BagOfWords *alocar_memoria() {
  return (BagOfWords*)malloc(1000*sizeof(BagOfWords));
} 

void compara_palavra(int *qtd, char *palavra, int *quantidadePalavras, BagOfWords *palavras) {
  int found, j;

  if (*qtd > 0){
    found =  0;
    for(j=0; j<*qtd; j++) {
      if(strcmp(palavras[j].palavra, palavra) == 0) {
        found= 1;
        palavras[j].quantidade++;
        break;
      }
    }
    if (found == 0){
      strcpy(palavras[*qtd].palavra, palavra);
      palavras[*qtd].quantidade = 1;
      *qtd += 1;
    }
    *quantidadePalavras += 1;
  }else{
    strcpy(palavras[*qtd].palavra, palavra);
    palavras[*qtd].quantidade = 1;
    *qtd += 1;
    *quantidadePalavras += 1;
  }
}

int ler_arquivo(int *quantidadePalavras, char *palavra, BagOfWords *palavras) {
  int qtd=0, j=0, tamanho=0;
  FILE *arquivo;

  arquivo = fopen("doc/texto.txt", "r");

  if(arquivo == NULL){
      printf("Arquivo vazio\n");
      return 0;
  }else{
    while(fscanf(arquivo,"%s ", palavra) != EOF){
      tamanho = strlen(palavra);
      for(j=0; j<tamanho; j++) palavra[j] = tolower(palavra[j]);

      if (tamanho <= 3) continue;

      for(j=0; j<tamanho; j++) {
        if(ispunct(palavra[j])) {
           palavra[j] = '\0';
           tamanho--;
        }
      }
      compara_palavra(&qtd, palavra, quantidadePalavras, palavras);
    }
  }
  fclose(arquivo);
  return qtd;
}

void bagofwords(int qtd, int quantidadePalavras, BagOfWords *palavras) {
  FILE *arquivo;
  int j;
  float percentual;

  arquivo = fopen("doc/bagofwords.csv", "w");

  for(j=0; j<qtd; j++){
    percentual = (float) palavras[j].quantidade*100/quantidadePalavras;
    fprintf(arquivo,"%s; %d; %.2f%\n", palavras[j].palavra, palavras[j].quantidade, percentual);
  }

  fclose(arquivo);
}

void ordenar(int qtd, BagOfWords *palavras) {
  int k, j, qtd_tmp;
  char tmp[30];

  for(k=0; k<qtd; k++){
    for(j=0;j<qtd;j++) {
      if(palavras[k].quantidade < palavras[j].quantidade){
        qtd_tmp = palavras[j].quantidade;
        palavras[j].quantidade = palavras[k].quantidade;
        palavras[k].quantidade = qtd_tmp;
        strcpy(tmp, palavras[j].palavra);
        strcpy(palavras[j].palavra, palavras[k].palavra);
        strcpy(palavras[k].palavra, tmp);
      }
    }
  }
}
