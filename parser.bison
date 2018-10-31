// Tokens
%token
  INT
  FLOAT
  VAR
  PLUS
  MINUS
  DIV
  MULT
  MOD
  GREATER
  LESS
  LESSTHAN
  GREATERTHAN
  EQUALS
  T_FLOAT
  T_INT
  T_MAIN
  T_FOR
  T_WHILE
  T_SCANF
  T_PRINTF
  T_IF
  T_ELSE
  T_OPENCURLYBRACKET
  T_CLOSECURLYBRACKET
  T_OPENPARENTESES
  T_CLOSEPARENTESES
  T_SEMICOLON
  T_AND
  T_OR
  T_NOT
  T_INCREMENT
  T_DECREMENT
  NAME
  EQUALSIGN

// Operator associativity & precedence
//so pus aqui as tokens todas ainda nao tem as precedencias corretas
%left T_MAIN T_FOR T_WHILE T_SCANF T_PRINTF T_IF T_ELSE T_OPENCURLYBRACKET T_CLOSECURLYBRACKET T_OPENPARENTESES T_CLOSEPARENTESES T_SEMICOLON T_AND T_OR T_NOT T_INCREMENT T_DECREMENT NAME
%left GREATER GREATERTHAN LESS LESSTHAN EQUALS EQUALSIGN
%left PLUS MINUS
%left DIV MULT MOD
%left T_FLOAT T_INT
%left INT FLOAT

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  float floatValue;
  char* nameValue;
  Expr* exprValue;
  BoolExpr* boolValue;
  Attrib* attribValue;
}

%type <intValue> INT
%type <exprValue> expr
%type <boolValue> boolexpr
%type <attribValue> attrib
%type <floatValue> FLOAT
%type <nameValue> NAME


// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
BoolExpr* root;
Attrib* root2;

}

%%


program:
  T_INT T_MAIN T_OPENPARENTESES T_CLOSEPARENTESES T_OPENCURLYBRACKET body T_CLOSECURLYBRACKET
  
body:
  boolexpr { root = $1; }
  |
  attrib { root2 = $1; }
  
attrib:
  T_INT NAME EQUALSIGN expr T_SEMICOLON{
    $$ = ast_attrib_expr_ct($2, $4);
  }
  |
  NAME EQUALSIGN expr T_SEMICOLON{
    $$ = ast_attrib_expr($1, $3);
  }
  |
  T_INT NAME T_SEMICOLON{
      $$ = ast_non_attrib($2);
  }
boolexpr:
  expr GREATERTHAN expr {
    $$ = ast_boolean_expr(GREATERTHAN, $1, $3);
  }
  |
   expr LESSTHAN expr {
    $$ = ast_boolean_expr(LESSTHAN, $1, $3);
  }
  |
   expr GREATER expr {
    $$ = ast_boolean_expr(GREATER, $1, $3);
  }
  |
   expr LESS expr {
    $$ = ast_boolean_expr(LESS, $1, $3);
  }
  |
   expr EQUALS expr {
    $$ = ast_boolean_expr(EQUALS, $1, $3);
  }

expr:
  INT {
    $$ = ast_integer($1);
  }
  |
  expr PLUS expr {
    $$ = ast_operation(PLUS, $1, $3);
  }
  |
  expr MINUS expr {
    $$ = ast_operation(MINUS, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MULT expr {
    $$ = ast_operation(MULT, $1, $3);
  }
  |
  expr MOD expr {
    $$ = ast_operation(MOD, $1, $3);
  }

  ;

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
