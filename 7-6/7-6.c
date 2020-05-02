#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_first_diff(FILE* f1,FILE* f2){
  char s1[1000]; char s2[1000];
  
  while ( fgets(s1,1000,f1) != NULL && fgets(s2,1000,f2) != NULL){
    if (strcmp(s1,s2) != 0){
      printf("file 1:%s\nfile 2:%s",s1,s2);
      return;
    }
  }
  if (strcmp(s1,s2) != 0){
    printf("file 1:%s\nfile 2:%s",s1,s2);
    return;
  }
}

int main(int argc, const char* argv[]){
  FILE* f1;
  FILE* f2;

  if (argc != 3){
    fprintf(stderr, "Usage: ./program file1 file2\n");
    return 0;  }
  f1 = fopen(argv[1],"r");
  f2 = fopen(argv[2],"r");

  if (f1 == NULL){
    fprintf(stderr, "Error: unable to access %s\n", argv[1]);
    return 0;
  }
  if (f2 == NULL){
    fprintf(stderr, "Error: unable to access %s\n", argv[2]);
    return 0;
  }

  print_first_diff(f1, f2);


  fclose(f1);
  fclose(f2);
}
