#include "dlist.h"

dnode* dnode_create(int data, dnode* prev, dnode* next){
  dnode *newnode = (dnode*)malloc(sizeof(dnode));
  newnode->data = data;
  newnode->prev = prev;
  newnode->next = next;
  return newnode;
}

dlist* dlist_create(void){
  dlist *newlist = (dlist*)malloc(sizeof(dlist));
  newlist->head = NULL;
  newlist->tail = NULL;
  newlist->size = 0;
  return newlist;
}

void dnode_print(dnode* a){
  if (a!=NULL)printf("%d\n",a->data);
}

void dnode_swap(dnode* a,dnode* b){
  if (a==b){return;}
  dnode* p = a->prev;
  dnode* n = a->next;
  dnode_print(a->next);
  dnode_print(b->next);
  dnode_print(a->prev);
  dnode_print(b->prev);
  
  a->next = b->next;
  if (a->next != NULL) a->next->prev = a;
  a->prev = b->prev;
  if (a->prev != NULL) a->prev->next = a;

  
  b->next = n;
  if (n != NULL) b->next->prev = b;
  b->prev = p;
  if (p != NULL) b->prev->next = b;
  dnode_print(a->next);
  dnode_print(b->next);
  dnode_print(a->prev);
  dnode_print(b->prev);
}

bool dlist_empty(dlist* list){return list->size == 0;}
size_t dlist_size(dlist* list){return list->size;}

void dlist_popfront(dlist* list){
  if (dlist_empty(list)){
    printf("List is empty\n");
    exit(1);
  }
  dnode* holder = list->head;
  if (list->size = 1) {
    list->head = NULL;
    list->tail = NULL;
  }else {
    list->head = list->head->next;
    list->head->prev = NULL;
    free(holder);
  }
  list->size -= 1;
}

void dlist_popback(dlist* l){
  if (dlist_empty(l)){
    printf("List is empty\n");
    exit(1);
  }
  dnode* holder = l->tail;
  if (l->size = 1) {
    l->head = NULL;
    l->tail = NULL;
  }else {
    l->tail = l->tail->prev;
    l->tail->next = NULL;
    free(holder);
  }
  l->size -= 1;
}

void dlist_pushfront(dlist* l, int data) {
  dnode* newhead ;
  if (dlist_empty(l)){
    newhead = dnode_create(data,NULL,NULL);
    l->head = newhead;
    l->tail = newhead;
  }
  else {
    newhead = dnode_create(data,NULL,l->head);
    l->head->prev = newhead;
    l->head = newhead;
  }
  l->size += 1;
}

void dlist_pushback(dlist* l, int data) {
  dnode* newtail;
  if (dlist_empty(l)){
    newtail= dnode_create(data,NULL,NULL);
    l->head = newtail;
    l->tail = newtail;
  }
  else {
    newtail = dnode_create(data,l->tail,NULL);
    l->tail->next = newtail;
    l->tail = newtail;
  }
  l->size += 1;
}

void dlist_clear(dlist* l){
  while(!dlist_empty(l)){
    dlist_popfront(l);
  }
}

void dlist_print(dlist* l, const char* msg){
  if (dlist_empty(l)){
    printf("List is empty\n");
    return;
  }
  printf("%s",msg);
  dnode* index = l->head;
  while(index){
    printf("%p <-- %d(%p) --> %p\n",(void*)index->prev,index->data,(void*)index,(void*)index->next);
    index = index->next;
  }
}

void dlist_swaptest(dlist* l){
  dnode_swap(l->head,l->tail);
  dnode* h = l->head;
  l->head = l->tail;
  l->tail = h;
}

int dlist_front(dlist* list){return list->head->data;}
int dlist_back(dlist* list){return list->tail->data;}
