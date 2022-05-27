#ifndef __flex_h_
#define __flex_h_

#include <stdio.h>

typedef enum {
    EOF_TOKEN,
    IF_TOKEN,
    FLOAT_TOKEN,
    IDENT_TOKEN,
    WHILE_TOKEN,
    REPEAT_TOKEN,
    INT_TOKEN,
    PRINT_TOKEN,
    L_PAREN_TOKEN,
    R_PAREN_TOKEN,
    SEMICOLON_TOKEN,
    ADDOP_TOKEN,
    MULTOP_TOKEN,
    ASSIGN_TOKEN
    //etc
} TOKEN;

int yylex(void);
void yyerror(char *s);

#endif
