#include <stdio.h> 
 
int main(void)  
{ 
	int NumberOfStudents = 0;      // Initialization, required 
	int NumberOfTeachers = 0;      // Initialization, required
       	float TotalRatio = 0.0;      // Initialization, required
	int Ratio = 0;
		
	printf("How many students does CSUCI have ?:"); 
	scanf("%d", &NumberOfStudents);     // Read input  
	
	printf("How many faculty does CSUCI have ?:");
	scanf("%d", &NumberOfTeachers);     // Read input 

	TotalRatio = (float) NumberOfStudents/NumberOfTeachers;	
	
	printf("At CSUCI, the ratio of student to faculty is %d where %.2f above is represents a real number with two decimal places.\n", Ratio, TotalRatio);

	return 0; 
} 
