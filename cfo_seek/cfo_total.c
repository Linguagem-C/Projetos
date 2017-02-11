#include "lib/library.h"

CFO_TOTAL *create_binary_tree_total() {
  CFO_TOTAL *root = (CFO_TOTAL*) malloc(sizeof(CFO_TOTAL));
  if(root != NULL)
    *root = NULL;
  return root;
}

void release_total(TOTAL *vertex) {
  if(vertex == NULL) return;
  release_total(vertex->left);
  release_total(vertex->right);
  free(vertex);
  vertex = NULL;
}

void release_binary_tree_total(CFO_TOTAL *root) {
  if(root == NULL) return;
  release_total(*root);
  free(root);
}

void search_line_total(CFO_TOTAL *root) {
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

int query_uf_binary_tree(CFO_TOTAL *root, char *UF) {
  TOTAL *current = *root;
  if(strcmp(UF, current->UF) == 0)
    return SUCCESS;
  else
    return FAIL;
}

void print_tree_in_order_of_total(CFO_TOTAL *root) {
  if(root == NULL) return;
  if(*root != NULL) {
    print_tree_in_order_of_total(&((*root)->left));
    search_line_total(root);
    print_tree_in_order_of_total(&((*root)->right));
  }
}

void print_tree_in_order_descendant(CFO_TOTAL *root, char *UF) {
  if(root == NULL) return;
  if(*root != NULL) {
    print_tree_in_order_descendant(&((*root)->right), UF);
    if(query_uf_binary_tree(root, UF))
      search_line_total(root);
    print_tree_in_order_descendant(&((*root)->left), UF);
  }
}

int insert_vertexs_ordered_by_total(CFO_TOTAL *root,  int line, char *UF, int total) {
  TOTAL *new_vertex;
  new_vertex = (TOTAL*) malloc(sizeof(TOTAL));
  new_vertex->line = line;
  strcpy(new_vertex->UF, UF);
  new_vertex->total = total;
  new_vertex->right = NULL;
  new_vertex->left = NULL;
  if(*root == NULL) {
    *root = new_vertex;
  } else {
    TOTAL *current = *root;
    TOTAL *previous = NULL;
    while(current != NULL) {
      previous = current;
      if(total > current->total)
        current = current->right;
      else
        current = current->left;
    }
    if(total > previous->total)
      previous->right = new_vertex;
    else
      previous->left = new_vertex;
  }
  return SUCCESS;
}

int create_ordered_binary_tree_by_total(CFO_TOTAL *root) {
  FILE *file;
  int close, line=1, i=0, total, success;
  char aux[100], UF[10];
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

    strcpy(UF, bag[0].word);
    total = atoi(bag[10].word);

    success = insert_vertexs_ordered_by_total(root, line, UF, total);

    i=0;
    line++;
  }
  close = fclose(file);

  if(close != 0) {
    printf("Erro no fechamento do arquivo!");
  }
  return success;
}
