
#include <stdlib.h>
#include <fileopen.h>

int main(int argc,const char* argv[]){
  if (openFiles(argc,argv) != false){
    fprintf(stderr, "Usage: ./fold inputfile outputfile int\n");
    return 1;
  }
  FILE* fin = fopen(argv[1],"r");
  FILE* fout = fopen(argv[2],"w");
  int count = 0;
  int t = atoi(argv[3]);
  
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

