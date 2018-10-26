#include <stdio.h>
#include "parser.h"



void print_aux(int nSpaces){
  int i;
  for(i=0;i<nSpaces;i++){
    printf("  ");
  }
}

void printVar(Expr* expr, int nSpaces){

}

void printExpr(Expr* expr, int nSpaces){

  if(expr->kind == E_INTEGER){
    print_aux(nSpaces);
    printf("%d\n", expr->attr.value);
  }
  else if(expr->kind == E_VAR){
    printVar(expr, nSpaces);
  }
  else if(expr->kind == E_OPERATION){

    print_aux(nSpaces);
    switch(expr->attr.op.operator){
      case PLUS:
        printf("+\n");
        break;
      case MINUS:
        printf("-\n");
        break;
      case MULT:
        printf("*\n");
        break;
      case DIV:
        printf("/\n");
        break;
      case MOD:
        printf("%c\n", '%');
        break;
              
    }

    printExpr(expr->attr.op.left, nSpaces+2);
    printExpr(expr->attr.op.right, nSpaces+2);
  }
  
}


void printBoolExpr(BoolExpr* boolExpr, int nSpaces){

  if(boolExpr->kind == E_BOOL){
    printExpr(boolExpr->attr.value, nSpaces);
  }
  else if(boolExpr->kind == E_BOOLOPERATION){
    print_aux(nSpaces);
    switch(boolExpr->attr.op.operator){
      case GREATER:
        printf(">\n");
        break;
      case LESS:
        printf("<\n");
        break;
      case GREATERTHAN:
        printf(">=\n");
        break;
      case LESSTHAN:
        printf("<=\n");
        break;
      case EQUALS:
        printf("==\n");
        break;  

    }

    printExpr(boolExpr->attr.op.left, nSpaces+2);
    printExpr(boolExpr->attr.op.right, nSpaces+2);



  }

}



int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {

     printBoolExpr(root, 0);
    
  }
  return 0;


}
