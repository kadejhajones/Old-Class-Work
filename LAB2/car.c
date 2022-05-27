#include <stdio.h> 
#include <ctype.h>
 
//#define DANGER_LEVEL 5     // The #define statement is used for constants. 
 

char level;
int main() { 
	
printf("With e for empty, f for full, and h for half full, how full is your car? \n>"); 
scanf("%c", &level);     // Read input   
	
switch( level ) {
	case 'e':
	case 'E': 
		printf("Empty.\n");
		break;
	case 'h':
	case 'H': 
		printf("Half Full.\n");
		break;
	case 'f':
	case 'F': 
		printf("Full.\n");
		break;
	case 'q':
	case 'Q':
		break;
		
	default: printf("Invalid input. Valid values are: F - Full, H - Half Full, E – Empty, Q - Quit Please try again or press q to quit.");
		break;
	}
	
	
	
	
	//if (level <= DANGER_LEVEL) 
	//	printf("Low on gas!\n"); 
	//else 
	//	printf("Good driver !\n"); 
		     
	return 0; 
} 
