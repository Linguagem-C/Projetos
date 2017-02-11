#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define SUCCESS 1
#define FALSE 0
#define FAIL 0
#define EQUAL 0
#define BIGGER 1
#define SMALLER -1

struct bag {
  char word[50];
};

struct cfo_city {
  int line;
  char city[50];
  struct cfo_city *left;
  struct cfo_city *right;
};

struct cfo_total {
  int line, total;
  char UF[10];
  struct cfo_total *left;
  struct cfo_total *right;
};

struct cfo_cds {
  int line, cds;
  struct cfo_cds *left;
  struct cfo_cds *right;
};

typedef struct bag BAG[11];
typedef struct cfo_city CITY;
typedef struct cfo_city *CFO_CITY;
typedef struct cfo_total TOTAL;
typedef struct cfo_total *CFO_TOTAL;
typedef struct cfo_cds CDs;
typedef struct cfo_cds *CFO_CDs;

int seekLine(FILE *file, int lineNumber, char *line);
void remove_line_break(char *string);
void read_string(char *string);
void clean_buffer();
int opening();
void menu(int option, CFO_CITY *city_root, CFO_CDs *cds_root, CFO_TOTAL *total_root);

CFO_TOTAL *create_binary_tree_total();
int query_uf_binary_tree(CFO_TOTAL *root, char *UF);
void print_tree_in_order_descendant(CFO_TOTAL *root, char *UF);
void print_tree_in_order_of_total(CFO_TOTAL *root);
int insert_vertexs_ordered_by_total(CFO_TOTAL *root,  int line, char *UF, int total);
int create_ordered_binary_tree_by_total(CFO_TOTAL *root);
void release_binary_tree_total(CFO_TOTAL *root);

CFO_CDs *create_binary_tree_cds();
void print_tree_in_order_of_cds(CFO_CDs *root);
int insert_vertexs_ordered_by_cds(CFO_CDs *root,  int line, int cds);
int create_ordered_binary_tree_by_cds(CFO_CDs *root);
void release_binary_tree_cds(CFO_CDs *root);

CFO_CITY *create_binary_tree_city();
void query_city_binary_tree(CFO_CITY *root, char *city);
void print_tree_in_order_of_city(CFO_CITY *root);
int insert_vertexs_ordered_by_city(CFO_CITY *root,  int line, char *city);
int create_ordered_binary_tree_by_city(CFO_CITY *root);
void release_binary_tree_city(CFO_CITY *root);
