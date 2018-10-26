%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++;}

([a-z]|[A-Z])([0-9]|[a-z]|[A-Z])+ {
    yylval.nameValue = yytext;
    return NAME;
}

\-?[0-9]+(\.[0-9]+)? {
    yylval.floatValue = atof(yytext);
    return FLOAT;
}

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}
"+" { return PLUS; }
"-" { return MINUS; }
"/" { return DIV;}
"%" { return MOD; }
"*" { return MULT; }
">" { return GREATER; }
"<" { return LESS; }
">=" { return GREATERTHAN; }
"<=" { return LESSTHAN; }
"==" { return EQUALS; }
"int" { return ATRIBINT; }
"float" { return ATRIBFLOAT; }
"=" { return EQUALSIGN; }
.  { yyerror("unexpected character"); }
%%

