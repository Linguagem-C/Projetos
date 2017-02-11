#include "lib/library.h"

int seekLine(FILE *file, int lineNumber, char *line) {
   int currentSeek = ftell(file);
   fseek(file, 0, SEEK_SET);
   while(--lineNumber && (fgets(line, 256, file) != NULL));

   if(!lineNumber)
      fgets(line, 256, file);

   fseek(file, currentSeek, SEEK_SET);

  return !lineNumber;
}

void read_string(char *string) {
  char caracter;
  int i = 0;
  do {
    caracter = getchar();
    if(caracter != '\n') {
      string[i] = caracter;
    }
    i++;
  }while(caracter != '\n' && caracter != '\0');
  string[--i] = '\0';
}

void remove_line_break(char *string) {
  size_t size;
  size = strlen(string);
  if (string[size - 1] == '\n')
    string[--size] = 0;
}

void clean_buffer(){
    int ch;
    do{
        ch = fgetc(stdin);
    }while (ch != EOF && ch != '\n');
}
