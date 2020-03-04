#include <stdio.h>
#include <assert.h>
#include <string.h>
#define MAXBUF 100

char* strcpy_(char*s, const char*t){
  char* p =s;
  while((*s++ = *t++) != '\0'){}
  return p;
}
void teststrcpy_(){
  char test[100] = "cat";
  assert(strcpy_("cat","doggy"));
}

char* strncpy_( char*s,const char*t, size_t n){
  char* p = s;
  while(n-- > 0 && (*s++ = *t++) != '\0'){}
  while((int)n-- > 0){*s++ = '\0';}
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
  while((int)n-- > 0 && *s != '\0' && *t != '\0' && *s == *t){
    ++s;
    ++t;
  }
  return *s - *t;
}

char* strcat_( char*s, const char*t){
   char* p = s;
  while (*s != '\0'){ s++;}
  while(*t != '\0'){*s++ = *t++;}
  return p;
}
void teststrcat_(){
  char test[100] = "cat";
  strcat_(test,"doggy");
  printf("%s\n", test);
}

char* strncat_( char*s, const char*t, size_t n){
  char* p = s;
  while (*s != '\0'){ s++;}
  while((int)n-- > 1 && *t != '\0'){*s++ = *t++;}
return p;
}
void teststrncat_(){
  char test[100] = "cat";
  strncat_(test,"doggy", 7);
  printf("%s\n", test);
}

char* strchr_( char* cs,char c){
  char*p = NULL;
  while(*cs != '\0' && *cs != c){cs++;}
  if (*cs == c){p = cs;}
  return p;
}
void teststrchr_(){
  const char* test = strchr_("cat",'a');
  printf("%s\n", test);
}

char* strrchr_(char* cs, char c){
  char*p = NULL;
  while(*cs != '\0'){
    if (*cs == c){p = cs;}
    cs++;
  }
  return p;
}

void teststrrchr_(){
  char* test = strrchr_("doggy",'g');
  printf("%s\n", test);
}

size_t strspn_(const char* cs, const char* ct){
  const char* p = ct;
  while(*cs != '\0' && strchr(ct,*cs) !=NULL){++ct;}
  return ct-p;
}

void teststrspn_(){
  size_t test = strspn_("cat","ca");
  printf("%lu\n", test);
}

size_t strcspn_(const char* cs, char* ct){
  const char* p = ct;
  while(*cs != '\0' && strchr(ct,*cs)==NULL){++ct;}
  return ct-p;
}

void teststrcspn_(){
  size_t test = strcspn_("elite","t");
  printf("%lu\n", test);
  test = strcspn_("elite","l");
  printf("%lu\n", test);
}

char *strpbrk_(const char* cs, char* ct){
  while(*cs != '\0'){
    if (strchr(cs,*ct) != NULL){return strchr(cs,*ct);}
    cs++;
  }
  return NULL;
}

void teststrpbrk_(){
  const char* test = strpbrk_("elite","ti");
  printf("%s\n", test);
  test = strpbrk_("elite","lei");
  printf("%s\n", test);
}

char *strstr_(const char* cs,const char* ct){
  const char* p = NULL;
  while(*cs != '\0'){
    if (strncmp(cs,ct,strlen(ct)) == 0){
      p = cs;
      return p;
    }
    else{
      cs++;
    }
  }

  return p;
}

void teststrstr_(){
  const char* test = strstr_("elite","ite");
  printf("%s\n", test);
  test = strstr_("starforce","force");
  printf("%s\n", test);
}

int strlen_(const char* cs){
  int i = 0;
  while (*cs != '\0'){
    i++;
    cs++;
  }
  return i;
}

void teststrlen_(){
  int test = strlen_("elite");
  printf("%d\n", test);
  test = strlen_("starforce");
  printf("%d\n", test);
}

int main(int argc, const char* argv[]){
  //teststrcat_();
  teststrncat_();
  teststrchr_();
  teststrrchr_();
  teststrspn_();
  teststrcspn_();
  teststrpbrk_();
  teststrstr_();
  teststrlen_();

}
