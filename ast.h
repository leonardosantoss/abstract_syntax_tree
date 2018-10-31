
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

typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _Attrib Attrib;




// Constructor functions (see implementation in ast.c)

Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolean(Expr *expr);
BoolExpr* ast_boolean_expr(int operator, Expr* left, Expr* right);
Attrib* ast_attrib_expr_ct(char* name, Expr* expr );
Attrib* ast_attrib_expr(char* name, Expr* expr );
Attrib* ast_non_attrib(char* name);


#endif
