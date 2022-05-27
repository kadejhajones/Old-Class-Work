%{
#include "y.tab.h"
%}

%option noyywrap

%{
    #include "calc.h"
    #define llog(token) {fprintf(flex_bison_log_file, "LEX: %s \"%s\"\n", #token, yytext);fflush(flex_bison_log_file);}
%}

letter      [a-zA-Z$_]+
digit       [0-9]
int         [+-]?{digit}+
float       [+-]?{digit}+\.{digit}*

%%
{float} {
	llog(FLOAT);
	yylval.dval = strtod(yytext, NULL);
        return FLOAT;	
}

{int} {
    llog(INT);
    yylval.dval = strtod(yytext, NULL);
    return INT;
}

")" {
    llog(R_PAREN);
    return R_PAREN;
}

"(" {
    llog(L_PAREN);
    return L_PAREN;
}

quit {
    llog(QUIT);
    return QUIT;
}

{letter} {
    llog(FUNC);
    yylval.fval = resolveFunc(yytext);
    return FUNC;
}

[\n] {
    llog(EOL);
    return EOL;
}

[\r\t ] {}; /* skip whitespace */

. {
    llog(ERROR INVALID);
}

%%
