#include "lib/library.h"

int main() {

	int option = 0;
  char exit = ' ';
  CFO_CITY *city_root;
  CFO_CDs *cds_root;
  CFO_TOTAL *total_root;

  city_root = create_binary_tree_city();
  cds_root = create_binary_tree_cds();
  total_root = create_binary_tree_total();

	while(1){
		system("clear");
		option = opening();
		menu(option, city_root, cds_root, total_root);
		printf("deseja voltar ao menu?(s/n): ");
		scanf(" %c", &exit);
		exit = toupper(exit);
		if(exit == 'N'){
			printf("Finalizando aplicação!!...\n");
      release_binary_tree_city(city_root);
      release_binary_tree_cds(cds_root);
      release_binary_tree_total(total_root);
			break;
		}
	}

	return 0;
}

