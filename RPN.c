#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define VAR 'a'



void push(double);
double pop();
int getop_(char*);
int getch_();
void ungetch_(int);
double atof_(const char*);


#define MAXVAL 100
size_t sp = 0;
double val[MAXVAL];

char buf[BUFSIZ];
int bufp = 0;


void rpm(){
    int type;
    double op2;
    char s[BUFSIZ];
    int vars[26];
    
    while((type = getop_(s)) != EOF){
      switch(type){
      case '\n': printf("\t%.8g\n",pop());
	break;
      case NUMBER: push(atof_(s));
	break;
      case '+': push(pop() + pop());
	break;
      case '*': push(pop() * pop());
	break;
      case '/': if ((op2 = pop()) == 0.0 ) {fprintf (stderr, "Error: attempt to divide by zero\n");
	  break;
	}
	push(pop() / op2);
	break;
      case '-': push(pop() - pop());
	break;
      case '%': push(fmod(pop() , pop()));
	break;
      case '^': push(pow(pop(),pop()));
	break;
      case '=': op2 = pop();
	if (isalpha(op2) == 2){
	  vars[op2 - 'a'] = pop();
	}
	else {push(op2);
	  fprintf(stderr, "Error: invalid variable name\n");
	}
	break;
      case '!': push(sin(pop()));
	break;
      case '@': push(cos(pop()));
	break;
      case '#': push(tan(pop()));
	break;
      case '$': op2 = pop();
	printf("\t%.8g\n",op2);
	push(op2);
	break;
      case '&': op2 = pop();
	push(op2);
	push(op2);
	break;
      case '~': push(exp(pop()));
	break;
	
      default:
	if (isalpha(type) == 2){push(vars[type - 'a']);}
	else {
	  fprintf(stderr, "error: unknown command\n");}
	break;
      }
    }
}

int main(int argc, const char* argv[]){
    rpm();
}

double pop(){
    if(sp==0){fprintf(stderr,"stack underflow\n");
        return 0.0;
    }
    else {return val[--sp];}
}
void push(double f){
    if (sp > MAXVAL){
        fprintf(stderr, "stack overflow\n");
    }
    else {val[sp++] = f;}
}

int getop_(char* s){
    int i, c;
    while((s[0] = c = getch_()) == ' ' || c == '\t'){}
    s[1] = '\0';

    if(!isdigit(c)&& c != '.'){return c;}
    
    i = 0;
    if (isdigit(c)){
        while (isdigit(s[++i] = c = getch_())){}
    }
    if (c == '.'){
        while (isdigit(s[++i] = c = getch_())){}
    }
    s[i] = '\0';
    if(c != EOF){
      ungetch_(c);
    }
    return NUMBER;
}

int getch_(){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch_(int c){
  if (bufp >= BUFSIZ) {fprintf (stderr , "Too many characters\n");}
  else {buf[bufp++] = c;}
}

double atof_(const char* s){
  double val,power;
  int i, sign;

  for (i = 0; isspace(s[i]);i++){;}

  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] -'0');
  if (s[i] == '.')
    i++;

  for (power = 1.0; isdigit(s[i]);i++){
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }
  return sign * val/power;
}

