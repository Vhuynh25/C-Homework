
#include "exer.h"

int pre_length = 6;

int main(int argc, const char* argv[]){
  if (argc < 2){
    fprintf(stderr,"Usage: ./program file");
    return 1;
  }
  
  if (opt_check(argv[1]) != 0){
    argv++;
  }

  FILE* f;
  if ((f = fopen(argv[1],"r")) == NULL) {
    fprintf(stderr,"Error opening file \n");
    return 0;
  }
  file_read(f);
  return 0;
}

struct wnode *walloc(){return (struct wnode *)malloc(sizeof(struct wnode));}
struct lnode *lalloc(){return (struct lnode *)malloc(sizeof(struct lnode));}

struct lnode *line_add(struct lnode *p,int l){
  if (p == NULL){
    p = lalloc();
    p->line = l;
    p->next = NULL;
  } 
  else if (p->line == l){
    return p;
  }
  else { p->next = line_add(p->next,l); }
  
    return p;
}

int strxspn(char* s1, char* s2){
  int count = 0;
  while (*s1++ == *s2++){count++;}
  return count;
}

struct wnode *word_add(struct wnode *p, char* w, int l){
  int cond, match; // need to change this func to add to *next
  
  if (p == NULL){
    p = walloc();
    p->word = strdup(w);
    p->next = NULL;
    p->down = NULL;
    p->line = line_add(p->line,l);
  }

  else if (strxspn(p->word,w) >= pre_length){
    p->down = word_add(p->down,w,l);
  }
  else
    { p->next = word_add(p->next,w,l); }
  
    return p;
}

void linesprint(struct lnode *p){
  if (p == NULL){
    printf("\n");
    return;}
  else {
    printf("%d, ", p->line);
    linesprint(p->next);
  }
}

void wordsprint(struct wnode *p){
  if (p == NULL){return;}
  if (p != NULL){
    printf("%s\n", p->word);
    //linesprint(p->line);
    wordsprint(p->down);
    wordsprint(p->next);
  }
}

int vars_check(char* s){
  if (strcmp("int",s) == 0 || strcmp("int*",s) == 0){
    return 1;
  }
  else if (strcmp("double",s) == 0 || strcmp("double* ",s) == 0) {
    return 1;
  }
  else if (strcmp("char ",s) == 0 || strcmp("char*",s) == 0){
    return 1;
  }
  else  if (strcmp("float",s) == 0 || strcmp("float*",s) == 0){
    return 1;
  }
  else if (strcmp("bool",s) == 0 || strcmp("bool*",s) == 0){
    return 1;
  }
  else if (strcmp("size_t",s) == 0 || strcmp("size_t* ",s) == 0){
    return 1;
  }
  return 0;
}

void file_read(FILE* f){
  struct wnode *tree = NULL;
  char* string = NULL;
  char* holder = NULL;
  char* ptr = NULL;
  char* set =  " \n[;";
  size_t zero = 0;
  int len, state;
  int lc = 1;
  state = 0; // state == 1 means in string, 2 for /* , 3 for //, -1 for add

  while (getline(&string,&zero,f) != -1){
    holder = strtok(string, set);
    while (holder != NULL){

      if ((ptr = strchr(holder,'\"')) != NULL && state == 0){

	*ptr = ';';
        state = 1;
      }
      else if ((ptr = strstr(holder,"/*")) != NULL && state == 0){

	*ptr = ';';
      	state = 2;
      }
      else if ((ptr = strstr(holder,"//")) != NULL && state == 0){

	*ptr = ';';
      	state = 3;
      }
      if (state == 1 && ((ptr = strrchr(holder,'\"')) != NULL)){
	// printf("%s \n",holder);
      	holder = ptr + 1;
      	state = 0;
      }
      else if (state == 2 && ((ptr = strstr(holder,"*/")) != NULL)){
      	holder = ptr + 2;
      	state = 0;
      }
      
      if (state > 0){}
      else if (vars_check(holder) == 1 && state == 0) {
	state = -1;
      }
      else if (state == -1){
	//holder = strtok(NULL, set);
	if ((ptr = strchr(holder,',')) == NULL){
	  state = 0;
	}
	else {	  *ptr = '\0';}
	if (strchr(holder,'(') == NULL && strchr(holder,')') == NULL){
	  tree = word_add(tree,holder,lc);
	}

      }
      holder = strtok(NULL, set);
     
    }
    if (state == 3){

      	state = 0;
    }
    lc++;
  }
  wordsprint(tree);
}

int opt_check(const char *s){
  if (strchr(s,'.')){return 0;}
  if (isdigit(*s) != 0){
    pre_length = atoi(s);
    return 1;
  }
  
  return 0; // if no option was found
}
