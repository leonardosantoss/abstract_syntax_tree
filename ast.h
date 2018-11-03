
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions


struct _Attrib{
  enum{
    E_ATTRIB,
    E_ATTRIBCT,
    E_NONATTRIB
  }kind;
  union{
    struct{
      struct _Expr* value;
      char* name;
    }att;
    struct{
      struct _Expr* value;
      char* name;
    }attct;
    char* name;
  }attr;
};

struct _Expr {
  enum { 
    E_INTEGER,
    E_VAR,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    char* var;
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _BoolExpr {
  enum{
    E_BOOL,
    E_BOOLOPERATION
  }kind;
  union{
    struct _Expr* value;
    struct{
      int operator;
      struct _Expr* left;
      struct _Expr* right;
    }op;
  }attr;
};

struct _While {
  enum{
    E_WHILE_EXPR,
    E_WHILE_BOOLEXPR
  }kind;
  union{
    struct _BoolExpr* valueBoolExpr;
    struct _Expr *valueExpr;
  }type;
  struct _Attrib *test;
};

struct _Cmd
{
  enum{
    E_ATTRIB,
    E_WHILE
  }kind;
  union{
    struct _Attrib *Attrib;
    struct _While *While;
  }type;
};

struct _CmdList
{
  struct _Cmd *Cmd;
  struct _CmdList *next;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _Attrib Attrib;
typedef struct _While While;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;



// Constructor functions (see implementation in ast.c)

Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolean(Expr *expr);
BoolExpr* ast_boolean_expr(int operator, Expr* left, Expr* right);
Attrib* ast_attrib_expr_ct(char* name, Expr* expr );
Attrib* ast_attrib_expr(char* name, Expr* expr );
Attrib* ast_non_attrib(char* name);
While* ast_cmd_while_expr(Expr* expr, Attrib* attrib);  //Shouldn´t be attrib, needs to be a cmdlist
While* ast_cmd_while_boolexpr(BoolExpr* boolexpr, Attrib* attrib);
CmdList* ast_cmdList(Cmd* cmd, CmdList* cmdList);
Cmd* ast_cmd_attrib(Attrib* attrib);
Cmd* ast_cmd_while(While* whileExpr);
#endif
