#include "lib/library.h"

CFO_CDs *create_binary_tree_cds() {
  CFO_CDs *root = (CFO_CDs*) malloc(sizeof(CFO_CDs));
  if(root != NULL)
    *root = NULL;
  return root;
}

void release_cds(CDs *vertex) {
  if(vertex == NULL) return;
  release_cds(vertex->left);
  release_cds(vertex->right);
  free(vertex);
  vertex = NULL;
}

void release_binary_tree_cds(CFO_CDs *root) {
  if(root == NULL) return;
  release_cds(*root);
  free(root);
}

void search_line_cfo(CFO_CDs *root) {
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

void print_tree_in_order_of_cds(CFO_CDs *root) {
  if(root == NULL) return;
  if(*root != NULL) {
    print_tree_in_order_of_cds(&((*root)->left));
    search_line_cfo(root);
    print_tree_in_order_of_cds(&((*root)->right));
  }
}

int insert_vertexs_ordered_by_cds(CFO_CDs *root,  int line, int cds) {
  CDs *new_vertex;
  new_vertex = (CDs*) malloc(sizeof(CDs));
  new_vertex->line = line;
  new_vertex->cds = cds;
  new_vertex->right = NULL;
  new_vertex->left = NULL;
  if(*root == NULL) {
    *root = new_vertex;
  } else {
    CDs *current = *root;
    CDs *previous = NULL;
    while(current != NULL) {
      previous = current;
      if(cds > current->cds)
        current = current->right;
      else
        current = current->left;
    }
    if(cds > previous->cds)
      previous->right = new_vertex;
    else
      previous->left = new_vertex;
  }
  return SUCCESS;
}

int create_ordered_binary_tree_by_cds(CFO_CDs *root) {
  FILE *file;
  int close, line=1, i=0, cds, success;
  char aux[100];
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

    cds = atoi(bag[2].word);

    success = insert_vertexs_ordered_by_cds(root, line, cds);

    i=0;
    line++;
  }

  close = fclose(file);

  if(close != 0) {
    printf("Erro no fechamento do arquivo!");
  }
  return success;
}

