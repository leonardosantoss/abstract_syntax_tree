
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions

struct _Var {
  enum{
    E_FLOAT,
    E_INT
  }type;
  char* name;
  union{
    int value;
    float value;
  } attr;
};

struct _Atrib{
  struct _Var* var;
  struct _Expr* value;
};

struct _Expr {
  enum { 
    E_INTEGER,
    E_VAR,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct _Var var;
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
typedef struct _Var Var;
typedef struct _Atrib Atrib;




// Constructor functions (see implementation in ast.c)

Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
BoolExpr* ast_boolean(Expr *expr);
BoolExpr* ast_boolean_expr(int operator, Expr* left, Expr* right);
Atrib* ast_atrib_Expr(Atrib* atrib, char* name, Expr* expr );
Atrib* ast_atrib()


#endif
