#include "lib/banFinan.h"


int main() {

  CLIENTE *cliente;

  quantidade_registros();

  printf("%d\n", qtd);

  cliente = aloca_memoria();

  ler_arquivo(cliente);

  aprovado(cliente);

  negados(cliente);

  liberar_memoria(cliente);

  return 0;
}
