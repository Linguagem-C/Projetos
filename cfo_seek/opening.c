#include "lib/library.h"

int opening() {
  int option = 0;
  system("clear");
  printf("**************************************************************************\n");
  printf("******************************** BEM VINDO! ******************************\n");
  printf("*Sistema de Consulta de cadastro do Conselho Federal de Odontologia (CFO)*\n");
  printf("**************************************************************************\n");
  printf("Escolha uma das opções dentro do sistema:\n");
  printf("1) Importar Dados\n");
  printf("2) Relatório completo\n");
  printf("3) Relatório de um estado\n");
  printf("4) Consultar dados de um municipio\n");
  printf("5) Sair\n");

  while(1){
    printf("Insira a opção: ");
    scanf("%d", &option);

    if(option <= 5)
      break;
  }

  return option;
}

int order_report_menu(){
  int option;
  system("clear");
  printf("Você escolheu a opção de mostrar relatorio completo\n");
  printf("Como você deseja ordenar o relatorio?\n");
  printf("1) Ordenar por município\n");
  printf("2) Ordenar por CD\n");
  printf("3) Ordenar por Total\n");
  printf("4) Voltar\n");

  while(1){
    printf("Insira a opção: ");
    scanf("%d", &option);

    if(option <= 5)
      break;
  }

  return option;

}

void menu(int option, CFO_CITY *city_root, CFO_CDs *cds_root, CFO_TOTAL *total_root) {
  char UF[10], city[50];
  int i, size, success_city, success_cds, success_total;

  system("clear");
  switch(option){
    case 1:
      printf("Você escolheu a opção de importar dados do CFO\n");
      success_city = create_ordered_binary_tree_by_city(city_root);
      success_cds = create_ordered_binary_tree_by_cds(cds_root);
      success_total = create_ordered_binary_tree_by_total(total_root);
      if(success_city && success_cds && success_total)
        printf("Dados inseridos com sucesso!\n");
      else
        printf("Houve um erro na inserção dos dados\n");
      break;

    case 2:
      printf("Você escolheu a opção de ver relatório completo\n");
      option = order_report_menu();
      if(option == 1){
        printf("Relatorio ordenado por municípios\n");
        printf("UF;CIDADE;CDs;EPAOs;TPDs;LBs;TSBs;ASBs;APDs;EPOs;TOTAL\n");
        print_tree_in_order_of_city(city_root);
      }else if(option == 2){
        printf("Relatorio ordenado por CD\n");
        printf("UF;CIDADE;CDs;EPAOs;TPDs;LBs;TSBs;ASBs;APDs;EPOs;TOTAL\n");
        print_tree_in_order_of_cds(cds_root);
      }else if(option == 3){
        printf("Relatorio ordenado pelo Total\n");
        printf("UF;CIDADE;CDs;EPAOs;TPDs;LBs;TSBs;ASBs;APDs;EPOs;TOTAL\n");
        print_tree_in_order_of_total(total_root);
      }else if(option == 4){
        option = opening();
        menu(option, city_root, cds_root, total_root);
      }
      break;

    case 3:
      printf("Você escolheu a opção de ver o relatório de um estado\n");
      printf("Insira a UF da pesquisa: ");
      scanf("%s", UF);
      size = strlen(UF);
      for(i=0; i<size; i++)
        UF[i] = toupper(UF[i]);
      printf("UF;CIDADE;CDs;EPAOs;TPDs;LBs;TSBs;ASBs;APDs;EPOs;TOTAL\n");
      print_tree_in_order_descendant(total_root, UF);
      break;

    case 4:
      printf("Você escolheu a opção de consultar os dados de um municipio\n");
      printf("Insira a cidade da pesquisa: ");
      clean_buffer();
      read_string(city);
      size = strlen(city);
      for(i=0; i<size; i++)
        city[i] = toupper(city[i]);
      printf("UF;CIDADE;CDs;EPAOs;TPDs;LBs;TSBs;ASBs;APDs;EPOs;TOTAL\n");
      query_city_binary_tree(city_root, city);
      break;

    case 5:
      printf("Finalizando!! ...\n");
      release_binary_tree_city(city_root);
      release_binary_tree_cds(cds_root);
      release_binary_tree_total(total_root);
      exit(0);
      break;
  }
}
