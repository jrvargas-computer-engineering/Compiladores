

%{
#include <math.h>
#include <stdio.h>
int yyerror (char const *s);
extern int yylex (void);
%}
%code requires { #include "asd.h" }

%union {
  double valor;
  asd_tree_t *arvore;
}

%token<valor> NUMBER
%token PLUS TIMES
%token LEFT RIGHT
%token END
%token END_OF_FILE
%type<arvore> E
%type<arvore> T
%type<arvore> F


%define parse.error verbose
%start Input

%%

Input: /* A entrada vazia é válida */;
Input: Input Line

Line: END
Line: END_OF_FILE { return EOF; }
Line: E END { printf("Expressão aritmética reconhecida com sucesso.\n"); asd_print_graphviz($1); asd_free($1); }
E: E PLUS T { 
    $$ = asd_new("+"); 
    asd_add_child($$, $1); 
    asd_add_child($$, $3); 
    $$->value = $1->value + $3->value;     
}
E: T { $$ = $1; }

T: T TIMES F { 
    $$ = asd_new("*"); 
    asd_add_child($$, $1); 
    asd_add_child($$, $3); 
    $$->value = $1->value * $3->value;
}

T: F { $$ = $1; }

F: LEFT E RIGHT { $$ = $2; }
F: NUMBER  {      
    char buf[32];
    sprintf(buf, "%.2f", $1);
    $$ = asd_new(buf);
    $$->value = $1;
}

%%

extern void yylex_destroy(void);
int yyerror(char const *s) {
  printf("%s\n", s);
  return 1;
}

int main() {
  int ret;
  do {
     ret = yyparse();
  } while(ret != EOF);
  printf("Fim.\n");
  yylex_destroy();
  return 0;
}
