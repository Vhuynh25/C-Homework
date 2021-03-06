#include <stdio.h>
#include <ctype.h>
#include <string.h>

int opt_check(const char *s){
  if (strcmp(s,"./upper") == 0){
    return 1;
  }
  if (strcmp(s,"./lower") == 0){
    return 0;
  }
  
  return 0; // if no option was found
}

void print_lower(FILE* f){
  char c;
  while ((c = fgetc(f)) != EOF){
    printf("%c",tolower(c));
  }
}

void print_upper(FILE* f){

  char c;
  while ((c = fgetc(f)) != EOF){
    printf("%c",toupper(c));
  }
}

int main(int argc, const char* argv[]){
  FILE* f;

  if (argc == 1){  f = fopen("stdin","r"); }
  else {  f = fopen(argv[1],"r");}
  if (f == NULL){
    fprintf(stderr, "Error: unable to access input\n");
    return 0;
  }
  
  if (opt_check(argv[0]) == 1){
    print_upper(f);
  }
  else {print_lower(f);}

  fclose(f);
}
