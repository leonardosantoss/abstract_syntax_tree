// AST constructor functions

#include <stdlib.h> // for malloc
#include <string.h>
#include "ast.h" // AST header


Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

BoolExpr* ast_boolean(Expr* expr){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->attr.value = expr;
  return node;
}

BoolExpr* ast_boolean_expr(int operator, Expr* left, Expr* right){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOLOPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Attrib* ast_attrib_expr_ct(char* name, Expr* expr){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind = E_ATTRIBCT;
  node->attr.attct.name = name;
  node->attr.attct.value = expr;
  return node;
}

Attrib* ast_attrib_expr(char* name, Expr* expr){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind = E_ATTRIB;
  node->attr.att.name = name;
  node->attr.att.value = expr;
  return node;
}

Attrib* ast_non_attrib(char* name){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind = E_NONATTRIB;
  node->attr.name = name;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

While* ast_cmd_while_boolexpr(BoolExpr* boolexpr, Attrib* attrib){
  While* node = (While*) malloc(sizeof(While));
  node->kind = E_WHILE_BOOLEXPR;
  node->type.valueBoolExpr = boolexpr;
  node->test = attrib;
  return node;
}


While* ast_cmd_while_expr(Expr* expr, Attrib* attrib){
  While* node = (While*) malloc(sizeof(While));
  node->kind = E_WHILE_EXPR;
  node->type.valueExpr = expr;
  node->test = attrib;
  return node;
}

Cmd* ast_cmd_while(While* whileExpr)
{
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_WHILE;
  node->type.While = whileExpr;
  return node;
}

Cmd* ast_cmd_attrib(Attrib* attrib)
{
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_ATTRIB;
  node->type.Attrib = attrib;
  return node;
}

CmdList* ast_cmdList(Cmd* cmd, CmdList* next)
{
  CmdList* list = (CmdList*) malloc(sizeof(CmdList));
  list->Cmd = cmd;
  list->next = next;
  return list;
}