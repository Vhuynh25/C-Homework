#include "fileopen.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  
  FILE* fin = fopen(argv[1], "r");
  if (fin == NULL){printf("Usage: program sourcefile");
    return 1;}
  int state, braces,par,brack,squote,dquote;
  
  char c;
  squote = dquote = brack = par = braces = state = 0;
  while ((c = fgetc(fin)) != EOF) {
    if (state == 1) {
      if (c == '\'') { state = 0;
	--squote;
      }
    }
    else if (state == 2) {
      if (c == '\"') {
	state = 0;
	--dquote;
      }
      
    }
    
    else if (state == 3) {
      if (c == '*' && (c = fgetc(fin)) == '/') {
	state = 0;
      }
    }
    else if (state == 4) {
      if (c == '\n') {
	state = 0;
      }
    }  
    else if (c == '/') {
      if ((c = fgetc(fin)) == '/') { state = 3; }
      else if ( c == '*') { state = 4; 
      }
    }
    else {
      printf("%c",c);
      if (c == '\'') { state = 1;
	++squote;
      }
      if (c == '\"') { state = 2;
	++dquote;
	
      }
      if (c == '{') {++braces;}
      if (c == '}') {--braces;}
      if (c == '(') {++par;}
      if (c == ')') {--par;}
      if (c == '[') {++brack;}
      if (c == ']') {--brack;}
     
    }
  }
  if (brack != 0){
    printf("Error: unmatched bracket(s) found\n");
  }
  if (par != 0){
    printf("Error: unmatched parenthesis found\n");
  }
  if (braces != 0){
    printf("Error: unmatched brace(s) found\n");
  }
  if (squote != 0){
    printf("Error: unmatched single quote(s) found\n");
  }
  if (dquote != 0){
    printf("Error: unmatched double quote(s) found\n");
  }
  
  fclose(fin);
  return 0;
}
