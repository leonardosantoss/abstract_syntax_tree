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
"main" { return T_MAIN; }
"for" { return T_FOR; }
"while" { return T_WHILE; }
"scanf" { return T_SCANF; }
"printf" { return T_PRINTF; }
"if" { return T_IF; }
"else" { return T_ELSE; }
"{" { return T_OPENCURLYBRACKET; }
"}" { return T_CLOSECURLYBRACKET; }
"(" { return T_OPENPARENTESES; }
")" { return T_CLOSEPARENTESES; }
";" { return T_SEMICOLUMN; }
"&&" { return T_AND; }
"||" { return T_OR; }
"!" { return T_NOT; }
"++" { return T_INCREMENT; }
"--" { return T_DECREMENT; }
.  { yyerror("unexpected character"); }
%%
