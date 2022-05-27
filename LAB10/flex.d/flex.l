/* NOTE: % must be in the first column (no indentation) */
/* add more regular expressions and returns for the other TOKEN types */


%option noyywrap
%option nounput
%option noinput

%{
	#include "flex.h"
%}

while 		"while"
letter          [a-z_$]
digit           [0-9]
int 		[0-9]+
float           {digit}+\.{digit}*
ident           {letter}+

%%
print       {return PRINT_TOKEN;}
while 	    {return WHILE_TOKEN;}
if          {return IF_TOKEN;}
repeat      {return REPEAT_TOKEN;}
{int}       {return INT_TOKEN;}
{float}     {return FLOAT_TOKEN;}
{ident}     {return IDENT_TOKEN;}
"("         {return L_PAREN_TOKEN;}
")"         {return R_PAREN_TOKEN;}
";"         {return SEMICOLON_TOKEN;}
"+"         {return ADDOP_TOKEN;}
"-"         {return ADDOP_TOKEN;}
"*"         {return MULTOP_TOKEN;}
"%"         {return MULTOP_TOKEN;}
"/"         {return MULTOP_TOKEN;}
"="         {return ASSIGN_TOKEN;}


<<EOF>>     {return EOF_TOKEN;}
[ \n\r\t]   ; //skip whitespace
.           {printf("ERROR: invalid character: >>%s<<\n", yytext);}

%%

