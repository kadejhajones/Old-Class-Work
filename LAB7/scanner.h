#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
typedef enum 
{ 
    NO_TOKEN_TYPE, 
    INVALID_TOKEN, 
    EOF_TOKEN, 
    FLOAT_TOKEN,
    INT_TOKEN,
    IDENT_TOKEN,
    MULT_OP,
    ADD_OP,
    R_PAREN,
    L_PAREN,
    SEMICOLON_TOKEN,
    EQUAL_TOKEN,
    KEYWORD_TOKEN,
    	
} TOKEN_TYPE; 
 
typedef union 
{ 
    long integer; 
    double floating_point; 
    char *string; 
    char op; 
} TOKEN_VALUE; 
 
typedef struct token 
{ 
    TOKEN_TYPE type; 
    TOKEN_VALUE val; 
} TOKEN; 
 
typedef enum 
{ 
    START_STATE, 
    KEYID_STATE,
    INT_STATE,
    FLOAT_STATE,
    INVALID_STATE,
  
} FSM_STATE; 
 
TOKEN *scanner(); 
void freeToken(TOKEN **); 
void printToken(TOKEN **);
