#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct lnode lnode;
struct lnode {
  int line;
  lnode* next;
};

typedef struct wnode wnode;
struct wnode {
  char* word;
  lnode* line;
  struct wnode *next;
};

void swap(wnode* prev, wnode* next){
  char* holder1 = next->word;
  lnode* holder2 = next->line;
  next->word = prev->word;
  next->line = prev->line;
  prev->word = holder1;
  prev->line = holder2;
  
}

int lnode_count(lnode* l){
  if (l == NULL) {return 0;}
  else {return 1 + lnode_count(l->next);}
}

void selection_sort(wnode* head){
  wnode* start = head;
  wnode* index;
  wnode* max;
  while (start->next != NULL){
    max = start;
    index = start->next;
    
    while (index != NULL){
      if (lnode_count(max->line) < lnode_count(index->line)){
	max = index;
      }
      index = index->next;
    }
    swap(start,max);
    start = start->next;
  }
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

struct wnode *word_add(struct wnode *p, char* w,int l){
  int cond, match; // need to change this func to add to *next
  
  if (p == NULL){
    p = walloc();
    p->word = strdup(w);
    p->next = NULL;
    p->line = line_add(p->line,l);
  } 
  else if (strcmp(p->word,w) == 0){
    p->line = line_add(p->line,l);
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
    printf("%s: \n", p->word);
    linesprint(p->line);
    wordsprint(p->next);
  }
}

void wordscount(struct wnode *p){
  if (p == NULL){return;}
  if (p != NULL){
    printf("%d %s \n", lnode_count(p->line), p->word);
    wordscount(p->next);
  }
}

void file_read(FILE* f){
  struct wnode *tree = NULL;
  char* string = NULL;
  char vars[1000] = "and ,the ,of ,as ,is ";
  size_t zero = 0;
  int lc = 1; 

  while (getline(&string,&zero,f) != -1){
    string = strtok(string, " ,.!?\n");
    while (string != NULL){
      //if (*(string+zero-2) == ' '){ *(string + zero - 2) = '\0';}
      if (strstr(vars,string) != NULL){}
      else {
	tree = word_add(tree,string,lc);
      }
      string = strtok(NULL, " ,.!?\n");
    }
    lc++;
  }
  //
  selection_sort(tree);
  wordscount(tree);
}

int main(int argc, const char* argv[]){
  if (argc != 2){
    fprintf(stderr,"Usage: ./program file");
    return 1;
  }
  FILE* f;
  if ((f = fopen(argv[1],"r")) == NULL) {
    fprintf(stderr,"Error opening file");
    return 1;
  }
  int c = 6;
  if (isdigit(argv[2]) != 0){c = atoi(argv[2]);} 
  file_read(f);
  return 0;
}
