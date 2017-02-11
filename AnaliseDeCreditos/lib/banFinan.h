#include <stdio.h>
#include <stdlib.h>

struct clientes {
  int codigo, idade;
  float salario, credito;
};

int i, qtd=0;

typedef struct clientes CLIENTE;

void quantidade_registros() {
  FILE *f;
  int idade, codigo;
  float salario;

  f = fopen("doc/cliente.txt", "r");

  if(f == NULL){
    printf("Erro na abertura do arquivo!");
    exit(1);
  }

  while(feof(f) == 0){
    fscanf(f, "%d; %f; %d", &codigo, &salario, &idade);
    qtd++;
  }
  qtd--;

  fclose(f);

}


CLIENTE *aloca_memoria() {

  CLIENTE *cliente;

  cliente = (CLIENTE*) malloc(qtd * sizeof(CLIENTE));

  if(cliente == NULL) {
    printf("Alocação falhou!\n");
  }

  return cliente;

}

void liberar_memoria(CLIENTE *cliente) {
  free(cliente);
}


void ler_arquivo(CLIENTE *cliente) {
  FILE *f;
  int fechou, qtd = 0;

  f = fopen("doc/cliente.txt", "r");

  if(f == NULL){
    printf("Erro na abertura do arquivo!");
    exit(1);
  }


  while(feof(f) == 0){
    fscanf(f, "%d; %f; %d", &cliente[qtd].codigo, &cliente[qtd].salario, &cliente[qtd].idade);
    qtd++;
  }
  qtd--;

  fechou = fclose(f);

  if(fechou != 0) {
    printf("Erro no fechamento do arquivo!");
  }
}

void aprovado(CLIENTE *cliente) {

  FILE *f;

  f = fopen("doc/aprovado.txt", "w");

  for(i=0; i<qtd; i++){
    if(cliente[i].salario > 2000.00 || cliente[i].idade > 30){
      cliente[i].credito = cliente[i].salario * 0.3;
      fprintf(f, "%d; %.2f; %.2f\n", cliente[i].codigo, cliente[i].salario, cliente[i].credito);
    }
  }

  fclose(f);

}

void negados(CLIENTE *cliente) {

  FILE *f;

  f = fopen("doc/negados.txt", "w");

  for(i=0; i<qtd; i++) {
    if(cliente[i].salario < 2000.00 || cliente[i].idade < 30)
      fprintf(f, "%d; %.2f\n", cliente[i].codigo, cliente[i].salario);
  }

  fclose(f);
}
