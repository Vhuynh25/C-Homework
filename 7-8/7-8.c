#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_page(FILE* f1){
  char c;
  while ( (c = fgetc(f1)) != EOF){
    printf("%c",c);
  }
  
}

int main(int argc, const char* argv[]){
  FILE* f1;

  if (argc == 1){
    fprintf(stderr, "Usage: ./program file1 file2 file3 etc\n");
    return 0;
  }

  int page = 1;
  while ((f1 = fopen(argv[1],"r")) != NULL){
    printf("-------------------------------\n");
    printf("page %d %20s\n", page, argv[1]);
    printf("-------------------------------\n");
    print_page(f1);
    fclose(f1);
    argv++;
    page++;
  }

}
