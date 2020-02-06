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
    return count
}

char* strcatx(char* to, char* from){
    char* p = to;
    to += strlen(to);
    while(*from! = '\0'){*to++=*from++;}
    return p;
}
