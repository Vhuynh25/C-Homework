#include <fileopen.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  if (argc != 4){fprintf(stderr, "Usage: ./entab inputfile outputfile int\n");}
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
  int state = 0;
  while((c = fgetc(fin)) != EOF){
    if (c == ' '){
      state = 1;
      ++count;
    }
    else if (state == 1){
      while (count >= t){
	fputc('\t',fout);
	count -= t;
      }
      while (count > 0){
	fputc(' ', fout);
	--count;
      }
    }
    else{
    fputc(c,fout);
    }
    
  }
  fclose(fin);
  fclose(fout);
  return 0;
  
}
