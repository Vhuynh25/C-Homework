#include "slist.h"

snode* snode_create(int data, snode* next){
  snode *newnode = (snode*)malloc(sizeof(snode));
  newnode->data = data;
  newnode->next = next;
  return newnode;
}

slist* slist_create(void){
  slist *newlist = (slist*)malloc(sizeof(slist));
  newlist->head = NULL;
  newlist->tail = NULL;
  newlist->size = 0;
  return newlist;
}

bool slist_empty(slist* list){return list->size == 0;}
size_t slist_size(slist* list){return list->size;}

void slist_popfront(slist* list){
  if (slist_empty(list)){
    printf("List is empty\n");
    exit(1);
  }
  snode* holder = list->head;
  if (list->size = 1) {
    list->head = NULL;
    list->tail = NULL;
  }
  else{
  list->head = list->head->next;
  free(holder);
  }
  list->size -= 1;
}

void slist_popback(slist* l){
  if (slist_empty(l)){
    printf("List is empty\n");
    exit(1);
  }
  if (l->size = 1) {
    slist_popfront(l);
  }
  else{
    snode* index = l->head;
    while(index->next != l->tail){index = index->next;}
    l->tail = index;
    free(index->next);
    index->next = NULL;
  }
  l->size -= 1;
}

void slist_pushfront(slist* l, int data) {
  snode* newhead ;
  if (slist_empty(l)){
    newhead = snode_create(data,NULL);
    l->head = newhead;
    l->tail = newhead;
  }
  else {
    newhead = snode_create(data,l->head);
    l->head = newhead;
  }
  l->size += 1;
}

void slist_pushback(slist* l, int data) {
  snode* newtail;
  if (slist_empty(l)){
    newtail = snode_create(data,NULL);
    l->head = newtail;
    l->tail = newtail;
  }
  else {
    newtail = snode_create(data,NULL);
    l->tail = newtail;
  }
  l->size += 1;
}

void slist_clear(slist* l){
  while(!slist_empty(l)){
    slist_popfront(l);
  }
}

void slist_print(slist* l, const char* msg){
  if (slist_empty(l)){
    printf("List is empty\n");
    return;
  }
  printf("%s",msg);
  snode* index = l->head;
  while(index){
    printf("%d(%p) --> %p\n",index->data,(void*)index,(void*)index->next);
    index = index->next;
  }
}

int slist_front(slist* list){return list->head->data;}
int slist_back(slist* list){return list->tail->data;}
