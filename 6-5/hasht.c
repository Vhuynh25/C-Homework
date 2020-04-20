#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASHSIZE 101

typedef struct entry entry;
struct entry{
  entry* next;
  char* name;
  char* defin;
};

void entry_undef(entry* n){
  n->defin = "NULL";
  n->name = "NULL";
}

static entry* table[HASHSIZE];
  
unsigned hash_func(char* s){
  unsigned val;
  for (val = 0; *s != '\0'; s++){
    val = *s + 31 * val;
  }
  return val % HASHSIZE;
}

entry* table_lookup(char* s){
  entry* ptr;
  for (ptr = table[hash_func(s)]; ptr != NULL; ptr = ptr->next){
    if(strcmp(s,ptr->name) == 0) {return ptr;}
  }
  return NULL;
}

void table_undef(char* s){
  entry* ptr = table_lookup(s);
  entry_undef(ptr);
}

entry* table_install(char* name, char* defin){
  entry* ptr;
  unsigned hashval;
  if ((ptr = table_lookup(name)) == NULL){
    ptr = (entry*)malloc(sizeof(entry));
    if ((ptr->name = strdup(name)) == NULL){
      return NULL;
    }
    hashval = hash_func(name);
    ptr->next = table[hashval];
    table[hashval] = ptr;
  }
  else if (ptr->name == "NULL" && ptr->defin == "NULL")
    {
      ptr->name = strdup(name);
      ptr->defin = strdup(defin);
    }
  else if (strcmp(ptr->defin,defin) != 0)
    { free((void*)ptr->defin);}
  if ((ptr->defin = strdup(defin)) == NULL){return NULL;}
  
  return ptr;
}

void table_print(){
  entry* index = table[0];
  while (index != NULL){
    printf("%s --- %s\n",index->name,index->defin);
    index = index->next;
  }
}

void table_clear(){
  entry* index = table[0];
  while (index != NULL){
    entry_undef(index);
    index = index->next;
  }
}

void table_printdefin(char* s){
  entry* index = table_lookup(s);
  while (index != NULL){
    if(strcmp(index->name,s) == 0){
      printf("%s\n",index->defin);
      return;
    }
    index = index->next;
  }
  printf("Entry not found\n");
}

void table_test(){
  printf("//-----Testing Hash Table-----//\n");
  table_install("cat","An animal that likes fish");
  table_install("dog","An animal that likes belly rubs");
  table_install("rabbit","An animal that likes carrots");
  table_install("mouse","An animal eaten by cats");
  table_install("virus","A pain in the neck");

  table_printdefin("cat");
  table_printdefin("dog");
  table_printdefin("bunny");
  table_printdefin("mouse");
  table_printdefin("rat");
  table_printdefin("virus");
  table_printdefin("bacteria");

  printf("//-----Testing undef \"Cat\"-----//\n");
  table_undef("cat");
  table_install("virus","A pain in the neck");
  
  table_printdefin("cat");
  
}

int main(int argc, const char* argv[]){
  table_test();
  return 0;
}
