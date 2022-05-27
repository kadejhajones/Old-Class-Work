#include <stdio.h> 
#include <stdlib.h> 
 
#define  SALARY   80000 
 
void main(int argc, char *argv[]) 
{
	int after_tax_distribution = 0; 
	int age = 0; 
	int amount = 0; 
	int distribution = 0; 
        int i = 0;
     	int matching_401k_amount = 0; 
        int max_matching_401k_amount = 0; 
        int principle = 0; 
        int taxes = 0; 
        int taxable_distribution; 
	int total_saved = 0; 
	int yearly_401k_contribution = 0; 
													 
        if (argc <= 2) { 
		printf("Missing input parameters to retire program.\n"); 
                printf("Usage: retire age_starting dollar_saved_per_month\n"); 
  		exit(0); 															
       	} 
			 
	age     = atoi(argv[1]); 
        amount  = atoi(argv[2]);	// NEED TO CORRECT. 
																 
	printf("\n"); 
	printf("Welcome to Your Retirement Calculator\n");
	printf("-----------------------------------------------------------------\n"); 
	printf("   1. You start saving at age %d.\n", age); 
	printf("   2. The amount saved per month is $%d.\n", amount); 
	printf("-----------------------------------------------------------------\n");

	for (i=age;i<65;i++) { 
		yearly_401k_contribution = 12 * amount;												
		principle = principle + yearly_401k_contribution; 
		// 6% of salary is matched at 50%.
		max_matching_401k_amount = (SALARY * .06) * .50;

		 if (yearly_401k_contribution >= max_matching_401k_amount)
			matching_401k_amount = max_matching_401k_amount;         // NEED TO CORRECT
		 else 
	              matching_401k_amount = yearly_401k_contribution * .5;         // NEED TO CORRECT

		// 1.107 is 10.7% gain.
		total_saved = (total_saved + (12 * amount)) * 1.107 + matching_401k_amount; 
		printf("At age %d, principle = $%d, total saved = $%d\n", 
		                       i, principle, total_saved); 
        } 

	printf("-----------------------------------------------------------------\n"); 
        printf("From age %d to 65, if $%d is saved per month:\n", age, amount); 
        printf("    The principle amount saved is  : $%d\n", principle); 
        printf("    The principle + gains amount is: $%d\n", total_saved); 
        printf("-----------------------------------------------------------------\n"); 
 
        printf("\n"); 
        printf("-----------------------------------------------------------------\n"); 
        printf("But how much money will I recieve per year from 65 to 95?\n"); 
        printf("-----------------------------------------------------------------\n"); 
 
        distribution = total_saved/(95-65);

// TO DO: Calculate IRS taxes for 2022 
// THE IF STATEMENTS ARE BASED ON 2021. NEED TO UPDATE FOR 2022.	

	if (distribution <= 10275) 
           taxes = (distribution * .1);    // NEED TO CORRECT.                            // 10% 
        else if (distribution <= 41775) 
           taxes = (10275 * .1) + (distribution - 10275) * 0.12;    // NEED TO CORRECt    // 12% 
        else if (distribution <= 89075) 
           taxes = (10275 * 0.10) + (48525 - 10275) * .12 + (distribution - 40525) * .22; // 22% 
        else if (distribution <= 170050) 
           taxes = (10275 * 0.10) + (48525 - 10275) * .12 + (89075 - 40525) * .22 + (distribution - 89075) * .24;  // 24% 
	else if (distribution <= 215950)
		taxes = (10275 * 0.10) + (48525 - 10275) * .12 + (89075 - 40525) * .22 + (170050 - 89075) * .24 + (distribution - 170050) * .32; // 32%
	else if (distribution <= 539900)
		           taxes = (10275 * 0.10) + (48525 - 10275) * .12 + (89075 - 40525) * .22 + (170050 - 89075) * .24 + (215950 - 170050) * .32 + (distribution - 215950) * .35; // 35%
	else if (distribution <= 539900)
		           taxes = (10275 * 0.10) + (48525 - 10275) * .12 + (89075 - 40525) * .22 + (170050 - 89075) * .24 + (215950 - 170050) * .32 + (539900 - 215950) * .35 + (distribution - 539900) * .37; // 37%
        after_tax_distribution = distribution - taxes; 
					 
        printf("   Distribution before taxes is: $%d\n", distribution); 
	printf("   Distribution after taxes is : $%d\n", after_tax_distribution); 
        printf("-----------------------------------------------------------------\n"); 
} 
