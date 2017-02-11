#include "lib/library.h"

CFO_CITY *create_binary_tree_city() {
  CFO_CITY *root = (CFO_CITY*) malloc(sizeof(CFO_CITY));
  if(root != NULL)
    *root = NULL;
  return root;
}

void release_city(CITY *vertex) {
  if(vertex == NULL) return;
  release_city(vertex->left);
  release_city(vertex->right);
  free(vertex);
  vertex = NULL;
}

void release_binary_tree_city(CFO_CITY *root) {
  if(root == NULL) return;
  release_city(*root);
  free(root);
}

void search_line_city(CFO_CITY *root) {
  FILE *file;
  int close;
  char aux[1000];

  file = fopen("doc/dadoscfo.csv", "r");

  if(file == NULL){
    printf("Erro na abertura do arquivo!");
    exit(1);
  }

  if(seekLine(file, (*root)->line, aux))
    printf("%s", aux);

  close = fclose(file);

  if(close != 0) {
    printf("Erro no fechamento do arquivo!");
  }
}

void query_city_binary_tree(CFO_CITY *root, char *city) {
  CITY *current = *root;
  while(current != NULL) {
    if(strcmp(city, current->city) == 0)
      search_line_city(&current);
    if(strcmp(city, current->city) > 0)
      current = current->right;
    else
      current = current->left;
  }
}

void print_tree_in_order_of_city(CFO_CITY *root) {
  if(root == NULL) return;
  if(*root != NULL) {
    print_tree_in_order_of_city(&((*root)->left));
    search_line_city(root);
    print_tree_in_order_of_city(&((*root)->right));
  }
}

int insert_vertexs_ordered_by_city(CFO_CITY *root,  int line, char *city) {
  CITY *new_vertex;
  new_vertex = (CITY*) malloc(sizeof(CITY));
  new_vertex->line = line;
  strcpy(new_vertex->city, city);
  new_vertex->right = NULL;
  new_vertex->left = NULL;
  if(*root == NULL) {
    *root = new_vertex;
  } else {
    CITY *current = *root;
    CITY *previous = NULL;
    while(current != NULL) {
      previous = current;
      if(strcmp(city, current->city) > 0)
        current = current->right;
      else
        current = current->left;
    }
    if(strcmp(city, previous->city) > 0)
      previous->right = new_vertex;
    else
      previous->left = new_vertex;
  }
  return SUCCESS;
}

int create_ordered_binary_tree_by_city(CFO_CITY *root) {
  FILE *file;
  int close, line=1, i=0, success;
  char aux[100], city[50];
  char *token;
  BAG bag;

  file = fopen("doc/dadoscfo.csv", "r");

  if(file == NULL){
    printf("Erro na abertura do arquivo!");
    exit(1);
  }

  while(1){
    if(feof(file)) break;

    fgets(aux, 100, file);
    remove_line_break(aux);

    token = strtok(aux, ";");
    while(token != NULL) {
      strcpy(bag[i].word, token);
      token = strtok(NULL, ";");
      i++;
    }

    strcpy(city, bag[1].word);

    success = insert_vertexs_ordered_by_city(root, line, city);

    i=0;
    line++;
  }
  close = fclose(file);

  if(close != 0) {
    printf("Erro no fechamento do arquivo!");
  }
  return success;
}
