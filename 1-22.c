
#include <stdlib.h>
#include "fileopen.h"
#define DEFAULT_INTERVAL 10

int main(int argc,const char* argv[]){
  if (openFiles(argc,argv) != true){
    fprintf(stderr, "Usage: ./fold inputfile outputfile int\n");
    return 1;
  }
  FILE* fin = fopen(argv[1],"r");
  FILE* fout = fopen(argv[2],"w");
  int count = 0;
  
    int t = argc == 4 ? atoi(argv[3]):DEFAULT_INTERVAL;
  
  char c;
  while((c = fgetc(fin)) != EOF){
    if (count % t == t-1 && c != '\n'){
      count = 0;
      fputc(c,fout);
      if (c != ' ' && c != '\t'){
	fputc('-',fout);
	fputc('\n',fout);
	
      }
      else {fputc('\n',fout);}
    }
    else if(count == 0){
      if (c != ' ' && c != '\t'){
	fputc('-',fout);
      }
      fputc(c,fout);
      count++;
    }
    else {
      fputc(c,fout);
      if (c == '\n'){count = 0;}
      count++;
    }
  }
  fclose(fin);
  fclose(fout);
  return 0;
}

