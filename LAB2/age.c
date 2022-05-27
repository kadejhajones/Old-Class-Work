#include <stdio.h> 
 
void main() 
{ 
	float age; 
	float monthsOld;
	float daysOld;
	float hoursOld;
	float secondsOld;
		 
	printf("How old are you? "); 
	scanf("%f", &age); 

	monthsOld = age * 12;
	daysOld = age * 365;
	hoursOld = daysOld * 24;
	secondsOld = hoursOld * 3600;
				 
	printf("You are %.02f years old.\n", age); 
	printf("You are %.02f months old.\n", monthsOld);
	printf("You are %.02f days old.\n", daysOld);
	printf("You are %.02f hours old.\n", hoursOld);
	printf("You are %.02f seconds old.\n", secondsOld);
} 
