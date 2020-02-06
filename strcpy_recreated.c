#include <stdio.h>

char* strcpyx(char* to, char* from){
    char* p = to;
    while(*from!='\0'){*to++=*from++;}
    return p;
}

int strlenx(char* s){
    int count = 0;
    while(*s != '\0'){count++;
        s++;
    }
    return count;
}

char* strcatx(char* to, char* from){
    char* p = to;
    while(*to != '\0'){++to;}
    while(*from != '\0'){*to++=*from++;}
    return p;
}

int main(int argc, const char* argv[]){
    char* a = "Hi, how are ya";
    char* b = "John";
    strcatx(a,b);
    printf("%s",a);
}
