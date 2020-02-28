#include <stdio.h>
#define MAXBUF 100

char* strcpy_(char*s, const char*t){
  char* p =s;
  while((*s++ = *t++) != '\0'){}
  return p;
}

char* strncpy_(char*s,const char*t, size_t n){
  char* p = s;
  while(n-- > 0 && (*s++ = *t++) != '\0'){}
  while(n-- > 0){*s++ = '\0';}
  return p;
}

int strcmp_(const char*s, const char*t){
  while(*s != '\0' && *t != '\0' && *s == *t){
    ++s;
    ++t;
  }
  return *s - *t;
}

int strncmp_(const char*s, const char*t, size_t n){
  while(*s != '\0' && *t != '\0' && *s == *t && n-- > 1){
    ++s;
    ++t;
  }
  return *s - *t;
}

char* strcat_( char*s, const char*t){
  char* p = s;
  while (*s != '\0'){ s++;}
  while((*s++ = *t++) != '\0'){}
  return p;
}

char* strncat_( char*s, const char*t, size_t n){
  char* p = s;
  while (*s != '\0'){ s++;}
  while((*s++ = *t++) != '\0' && n-- > 1){}
  return p;
}


int main(int argc, const char* argv[]){
  char test[100] = "cat";
  //strncpy_(test,"doggy", 4);
  strncat_(test,"doggy", 4);
  printf("%s\n",test);
}
