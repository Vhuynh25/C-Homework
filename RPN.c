
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define VAR 'a'
#define MATH '1'



void push(double);
double pop();
int getop_(char*);
int getch_();
void ungetch_(int);
double atof_(const char*);
void doFuncs();
void math(char*);
void built_string(char*);

#define MAXVAL 100
size_t sp = 0;
double val[MAXVAL];

char buf[BUFSIZ];
int bufp = 0;



struct tnode {
  char*word;
  double val;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree (struct tnode*, char *,double);
void treeprint(struct tnode*);
double getvar(struct tnode*, const char*);
struct tnode *talloc(){return (struct tnode *)malloc(sizeof(struct tnode));}
char *strdupe(char *s){
  char *p;
  p = (char*) malloc(strlen(s)+1);
  if (p != NULL){
    strcpy(p,s);
  }
  return p;
}

void rpm(){
    int type;
    double op2;
    char s[BUFSIZ];
    int last;
    struct tnode* vars;
    char varname[MAXVAL];
    int i;

    while((type = getop_(s)) != EOF){
      switch(type){
      case '\n': printf("\t%.8g\n",pop());    break;
      case NUMBER: push(atof_(s));            break;
      case '+': push(pop() + pop());          break;
      case '*': push(pop() * pop());          break;
      case '-': push(pop() - pop());          break;
      case '%': push(fmod(pop() , pop()));    break;
      case '^': push(pow(pop(),pop()));       break;
      case MATH: math(s);                     break;

      case '=': i = 0;
      while((s[0] = c = getch_()) == ' ' || c == '\t'){}
      while(isalpha(varname[i++] = getc(stdin))){}
      varname[i] = '\0';
      addtree(vars,varname,pop());            break;

      case '?': i = 0;
      while((s[0] = c = getch_()) == ' ' || c == '\t'){}
      while(isalpha(varname[i++] = getc(stdin))){}
      varname[i] = '\0';
      getvar(vars,varname);                   break;

      case '/': if ((op2 = pop()) == 0.0 ) {
        fprintf (stderr, "Error: attempt to divide by zero\n");
        break;
      }
        push(pop() / op2);                    break;

      default:
	     fprintf(stderr, "error: unknown command\n");
       break;
      }
      last = type;
    }
    return;
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

    if(!isalnum(c)&& c != '.'){return c;}
    i = 0;
    if (isdigit(c)){
        while (isdigit(s[++i] = c = getch_())){}
    }
    if (c == '.'){
        while (isdigit(s[++i] = c = getch_())){}
    }
    if (isalpha(c)){
      while(isalpha(s[++i] = c = getch_())){}
      s[i] = '\0';
      return MATH;
    };

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

void math(char* s){
  double op1, op2, result;
  if (strcmp(s, "sin") == 0){
    result = sin(pop());
  }
  if (strcmp(s, "cos") == 0){
    result = cos(pop());
  }
  if (strcmp(s, "tan") == 0){
    result = tan(pop());
  }
  if (strcmp(s, "top") == 0){
    result = pop();
    push(result);
  }
  if (strcmp(s, "dupe") == 0){
    result = pop();
    push(result);
    push(result);
  }
  if (strcmp(s, "exp") == 0){
    result = exp(pop());
  }

  push(result);
  //printf("\t%.8g\n",result);
}

struct tnode *addtree(struct tnode *p, char* w,double val){
  int cond;
  if (p ==NULL){
    p = talloc();
    p->word = strdup(w);
    p->val = val;
    p->left = p->right = NULL;
  } else if((cond = strcmp(w, p->word)) == 0)
    {p->val = val;}
    else if (cond < 0){
      p->left =addtree(p->left,w, val);
    }
    else {
      p->right = addtree(p->right,w, val);
    }
    return p;
}
void treeprint(struct tnode *p){
  if (p!=NULL){
    treeprint(p->left);
    printf("%s: %4f\n", p->word, p-> val);
    treeprint(p->right);
  }
}

double getvar(struct tnode *p, const char* w){
  int cond;
  if (p == NULL)   {
    return 0.0;
  }
  else if((cond = strcmp(w, p->word)) == 0) {return p->val;}
  else if (cond < 0){
    return getvar(p->left,w);
  }
  else {
    return getvar(p->right,w);
  }
}

void built_string(char *s){

}
