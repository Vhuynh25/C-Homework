#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  if (argc != 4){fprintf(stderr, "Usage: ./detab inputfile outputfile int\n");}
  FILE* fin = fopen(argv[1],"r");
  FILE* fout = fopen(argv[2],"w");
  int count = 0;
  int t = atoi(argv[3]);
  
  if (fin == NULL){
    fprintf(stderr, "Input file could not be opened");
    return 1;
  }
  if (fout == NULL){
    fprintf(stderr, "Output file could not be opened");
    return 1;
  }

  char c;
  while((c = fgetc(fin)) != EOF){
    if (c == '\t'){
      while (count % t != 0){
	fputc(' ', fout);
	count++;
      }
    }
    else {
      fputc(c,fout);
      count++;
    }
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
