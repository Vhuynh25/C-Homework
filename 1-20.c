#include "fileopen.h"
#include <stdlib.h>
#define DEFAULT_INTERVAL 10

int main(int argc, const char* argv[]){
  if (openFiles(argc,argv) != true){fprintf(stderr, "Usage: ./detab inputfile outputfile int\n");}
  FILE* fin = fopen(argv[1],"r");
  FILE* fout = fopen(argv[2],"w");
  int count = 0;
  int t = argc == 4 ? atoi(argv[3]):DEFAULT_INTERVAL;
  
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
