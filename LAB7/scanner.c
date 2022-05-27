#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
 
#include "scanner.h" 
 
#define BUFFER_SIZE 32 
 
 
// clean up the referenced token (if it isn't NULL). 
 
void freeToken(TOKEN **token) 
{ 
	if (*token == NULL){
		return;
	}	
	if((*token)->type == KEYWORD_TOKEN ||(*token)->type == IDENT_TOKEN ||(*token)->type == INVALID_TOKEN){
		free((*token)->val.string);
	}
	free(*token);
} 
 
void printToken (TOKEN **token) 
{ 
    /* 
     * Print the referenced token in a readable format. 
     * Displayed information should include the token's type, 
     * and also the token's value if applicable. 
     * 
     * Check the sample runs for an example format. 
     */ 

	switch((*token)->type){
		case NO_TOKEN_TYPE:
			break;
		case INVALID_TOKEN:
			printf("<INVALID, %s>\n", (*token)->val.string);
			break;
		case EOF_TOKEN:
			printf("<EOF>\n");
			break;
		case FLOAT_TOKEN:
			printf("<FLOAT, %f>\n",(*token)->val.floating_point);
			break;
		case INT_TOKEN:
			printf("<INT, %ld>\n", (*token)->val.integer);
			break;
		case IDENT_TOKEN:
			printf("<IDENT, %s>\n", (*token)->val.string);
			break;
		case MULT_OP:
			printf("<MULT_OP, %c>\n", (*token)->val.op);
			break;
		case ADD_OP:
			printf("<ADD_OP, %c>\n", (*token)->val.op);
			break;
		case R_PAREN:
			printf("<RPAREN>\n");
			break;
		case L_PAREN:
			printf("<LPAREN>\n");
			break;
		case SEMICOLON_TOKEN:
			printf("<SEMICOLON>\n");
			break;
		case EQUAL_TOKEN:
			printf("<ASSIGN>\n");
			break;
		case KEYWORD_TOKEN:
			printf("<KEYWORD, %s> \n", (*token)->val.string);
			break;
	}

} 
 
void checkKeywordOrID(TOKEN *token, char *str) 
{ 
    /* 
     * For use in the scanner function, to differentiate between keywords 
     * and identifiers (which are treated identically by the state machine). 
     * 
     * Check if the collected token is a keyword by comparing the string 
     * value arg to the string values of the keywords (print and repeat). 
     * If the string value denotes is a print or repeat token, change its 
     * type to the corresponding TOKEN_TYPE. 
     * 
     * If the token is not a keyword, then it is an identifier. Change its 
     * type accordingly, and store its string value. Note that the str 
     * argument is the scanner's buffer, so it should not be assigned 
     * directly, but copied; the buffer will be freed before the token 
     * is returned (see the bottom of the scanner function). 
     * 
     * Recall, to copy a string: 
     * 1. Allocate enough space to store the string (including the null terminator). 
     * 2. Copy the characters into this new space from the original. 
     */ 

	if (strcmp(str, "print") == 0 || strcmp("repeat", str) == 0){
		(*token).type = KEYWORD_TOKEN;	
	}else{
		(*token).type = IDENT_TOKEN;
	}
	
	token->val.string = strdup(str);
} 

TOKEN *scanner() 
{ 
    /* 
        stringValue is a buffer to store a token's contained characters 
        while it is being lexed. You should add characters to it like an 
        array, and be sure to keep the stringValueIndex up to date so you 
        know where the next character should go. 
 
        Dont forget to terminate string values when they're complete! 
    */ 
    size_t bufferSize = BUFFER_SIZE; 
    char *stringValue = calloc(sizeof(char), bufferSize); 
    int stringValueIndex = 0; 
 
    // allocate space for the new token 
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN)); 
 
    // initialize the token type to denote that the token is in progress 
    token->type = NO_TOKEN_TYPE; 
 
    // set state machine to starting state 
    FSM_STATE state = START_STATE; 
 
    char currentChar = '\0'; 

 
 
    while (currentChar != EOF && token->type == NO_TOKEN_TYPE) 
    { 
        currentChar = (char) getchar(); 
        /* 
         * Given the current state of the state machine 
         * and the next character, update the state machine 
         * (and the string value of the token being built, 
         * if applicable). 
         * 
         * DO NOT return anything here. The only return is the 
         * one at the end of this function. Note that the while 
         * loop stops iterating once token->type is updated, so 
         * token->type should only be updated once the token is 
         * ready to be returned. 
         */ 
 	//creating a switch to gover everything 
	switch(state){
		case START_STATE:
			switch(currentChar){
				case '(':
					break;

				}
			state=
			break;
		case KEYID_STATE:
			break;
		case INT_STATE:
			break;
		case FLOAT_STATE:
			break;
		case INVALID_STATE:
			break;

        // if the buffer is full, quadruple its size (do not edit) 
        if (stringValueIndex >= bufferSize-1) 
        { 
            bufferSize *= 4; 
            char *temp = calloc(sizeof(char), bufferSize); 
            strcpy(temp, stringValue); 
            free(stringValue); 
            stringValue = temp; 
        } 
    } 
 
    free(stringValue); 
    return token;                                                                                                                                                                                                                                                                                                                                                                                                                                          return token;
 }
