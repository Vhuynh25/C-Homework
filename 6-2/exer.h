#ifndef exer_h
#define exer_h
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
  struct wnode* down;
  struct wnode* next;
};

struct wnode *walloc();
struct lnode *lalloc();

struct lnode *line_add(struct lnode *p,int l);
struct wnode *word_add(struct wnode *p, char* w,int l);

void linesprint(struct lnode *p);
void wordsprint(struct wnode *p);

int opt_check(const char* s);

int strxspn(char* s1, char* s2);

char* strsplit(char* string,char* ptr);

void file_read(FILE* f);

int vars_check(char* s);

int opt_check(const char* s);

#endif /* exer_h */
