/* -----------------------------------------------------------------------------
Program file: tsudamp2.c 
Author:       Makiko Tsuda
Date:         9/26/2021
Class:		  Intro to Programming with C Part 2
Assignment:   #2 
Objective:    The program prompts a user for the number of hours worked and 
			  hourly rate for the worker and culculates the gross pay, tax, 
			  and net pay for up to 20 employees. At the end, 
			  a payroll summary is printed.			   
------------------------------------------------------------------------------*/
#include <stdio.h>
#include<string.h> 

/* Function Prototypes */
int   get_company_name(char[]);
int   get_num_employees();
float calculate_overtime_pay(float, float);
float calculate_gross_pay(float, float, float);
float calculate_fedtax(float);
float calculate_net_pay(float, float);

/* Struct Definition */
struct employee
{
	char  emp_name[30];
	float emp_hrs;
	float emp_rate;
	float emp_gross;
	float emp_net;
	float emp_tax;
};

int main(void) 
{
	/* Variable Declarations */
	char 	company_name[30];				/* Company Name 					  */
	int  	num_employees;					/* Number of employees, max 20 		  */
	float	hours_worked;					/* the num of hours the worker worked */
	float	hourly_rate;					/* the pay rate for the worker		  */
	float	overtime_pay;					/* Overtime pay 					  */
	struct	employee emp[20];				/* a struct array of employees		  */
	float	total_gross_pay = 0;			/* Total Gross pay of all workers	  */
	float	total_tax = 0;					/* Total Fed Tax of all workers		  */
	float	total_net_pay = 0;				/* Total Net Pay of all workers		  */
	char	c;								/* for buffer clearing 				  */
	int 	i, x;							/* counters 						  */
	
	/* Welcome Message and get user inputs */
	printf("\n\n");
	printf("***** Welcome to the Intro to Programming Payroll Anapysis *****\n\n");
	/* Get the company name */
	get_company_name(company_name);
	/* Get the number of employees to analyze */
	num_employees = get_num_employees();
	
	for ( i = 0; i < num_employees; i++ )
	{
		/* Get employee's name and store it in the struct */
		printf("\nEnter the name for employee %d: ", i+1);
		scanf("%30[^\n]s", emp[i].emp_name);
		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
		
		/* Get the hours worked and store it in the struct */
		do
		{
			printf("Enter the number of hours employee %d worked: ", i+1);
			scanf("%f", &emp[i].emp_hrs);
			while ((c = getchar() != '\n') && c != EOF); /* clear buffer */	
			
			/* the number of hours has to be larger than 0 */
			if ( emp[i].emp_hrs < 0 )
			{
				printf("Please enter a number larger than 0.\n\n");	
			} /* End if */
			
		} while ( emp[i].emp_hrs < 0 ); /* End do while */
		
		/* Get the rate and store it in the struct */
		do
		{
			printf("Enter the hourly rate for employee %d: ", i+1);
			scanf("%f", &emp[i].emp_rate);
			while ((c = getchar() != '\n') && c != EOF); /* clear buffer */	
			
			/* the rate has to be larger than 0 */
			if ( emp[i].emp_rate < 0 )
			{
				printf("Please enter a number larger than 0.\n\n");	
			} /* End if */
			
		} while ( emp[i].emp_rate < 0 ); /* End do while */
		
		/* Calculate overtime pay */
		overtime_pay = calculate_overtime_pay(emp[i].emp_rate, emp[i].emp_hrs);
		
		/* Calculate Gross Pay */
		emp[i].emp_gross = calculate_gross_pay(emp[i].emp_hrs , emp[i].emp_rate, overtime_pay);
		
		/* Calculate Tax */
		emp[i].emp_tax = calculate_fedtax(emp[i].emp_gross);
		
		/* Calculate Net Pay */
		emp[i].emp_net = calculate_net_pay(emp[i].emp_gross, emp[i].emp_tax);
		
		/* Updating the total for the company */
		total_gross_pay += emp[i].emp_gross;
		total_tax += emp[i].emp_tax;
		total_net_pay += emp[i].emp_net;		

	} /* End for loop */
		
	/* Print the Summary */
	/* Print the header */
	/* Centering the output - adapted from the class resource */
	printf("\n\n");
	printf ("                      Payroll Report\n");
	for ( x = 1; x < (60 - strlen(company_name))/2; x++ )
 		printf(" ");// skips half of the white space to center the company name
		printf("%s\n",company_name);
		
	/* ----------------------------------------------------------------------------- */
	/* This underlines the entire Company Name no matter how big (extra not required)*/
	/* ----------------------------------------------------------------------------- */
	for ( x = 1; x < (60 - strlen(company_name))/2; x++ )
 		printf(" ");// skips half of the white space to center the underlining
	for ( x = 1; x <= strlen(company_name); x++ )// prints as many dashes as the length of the company name
		printf("-");
				
	printf("\n\n");	
	
	/* Summary per employee */
	for (i = 0; i < num_employees; i++ )
	{
		printf("\t\t%s\n", emp[i].emp_name);
		printf("\t\tGross Pay: \t$ %10.2f\n", emp[i].emp_gross);
		printf("\t\tFederal Tax: \t$ %10.2f\n", emp[i].emp_tax);
		printf("\t\tNet Pay: \t$ %10.2f\n\n", emp[i].emp_net);
	} /* End for */
	
	/* Print the Company-wide Total 						  */
	/* Centering the output - adapted from the class resource */
	printf("\n\n");
	printf("                      Report Totals\n");
		
	/* ----------------------------------------------------------------------------- */
	/* This underlines the entire Company Name no matter how big (extra not required)*/
	/* ----------------------------------------------------------------------------- */
	for(x = 1; x < (60 - strlen(company_name))/2; x++)
 		printf(" ");// skips half of the white space to center the underlining
	for(x = 1; x <= strlen(company_name); x++)// prints as many dashes as the length of the company name
		printf("-");
				
	printf("\n\n");
	printf("\t\tGross Pay: \t$ %10.2f\n", total_gross_pay);
	printf("\t\tFederal Tax: \t$ %10.2f\n", total_tax);
	printf("\t\tNet Pay: \t$ %10.2f\n", total_net_pay);
	
 	getchar(); /* to suspend the program before exiting */	
 	
	return 0;
} /* End main */

/********** Functions ******************/

/* Prompt for and capture the company name */
int get_company_name(char company_name[])
{
	/* Variable Declarations */
	char c;					/* buffer clearing 		*/
	int  max_char = 30;		/* # of max character 	*/
	
	printf("Enter the Company Name (up to 29 characters): ");
	scanf("%30[^\n]s", company_name);
 	while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
 	
 	return 0;
 	
} /* End get_company_name */

/* Prompt for and capture the number of employees to process */
int get_num_employees()
{
	/* Variable Declarations */
	float num_employees;	/* user input 			*/
	char  c;				/* for buffer clearing  */
	
	/* Prompt for the number of employees */
	/* Validate the user input 			  */
	do
	{
		printf("Enter the number of employees(1-20): ");
		scanf("%f", &num_employees);
 		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */	
 		
 		if( num_employees < 0 || num_employees > 20 )
 		{
 			printf("Please enter a value between 0 and 20.\n\n");
 		} /* End if */
 		
	} while ( num_employees < 0 || num_employees > 20 ); /* End do while */
 	
	return num_employees;
	
} /* End get_num_employees */

/* calculate the overtime portion of pay only */
float calculate_overtime_pay(float hourly_rate, float hours_worked)
{
	/* Variable Declarations */
	float	overtime_pay;		/* overtime pay 			*/
	float	std_hours = 40.0;	/* standard work hours 		*/
	float	overtime_hours;		/* hours beyond 40 hours 	*/
	
	/* If worked more than 40 hours, how many overtime hours ? */
	if ( hours_worked > std_hours )
	{
		overtime_hours = hours_worked - std_hours;
	} /* End if */
	else
	{
		overtime_hours = 0;		
	} /* End else */

	/* calculate overtime pay */
	overtime_pay = overtime_hours * hourly_rate * 1.5;

	return overtime_pay;
	
} /* End calculate_overtime_pay */

/* calculate standard pay portion only */
float calculate_gross_pay(float hours_worked, float hourly_rate, float overtime_pay)
{
	/* Variable Declarations */
	float	gross_pay;			/* Store gross pay */
	float	std_hours = 40.0;	/* Standard work hours */
	
	if (hours_worked > std_hours)
	{
		/* if worked more than standard hours, 	*/
		/* ignore the overtime hours			*/
		gross_pay = std_hours * hourly_rate + overtime_pay;
	} /* End if */	
	else
	{
		/* if within standard hours, multiply the hours and rate */
		gross_pay = hours_worked * hourly_rate + overtime_pay;
	} /* End else */
	
	return gross_pay;
	
} /* End calculate_gross_pay */

/* Calculate the federal tax portion only */
float calculate_fedtax(float gross_pay)
{
	/* Variable Declarations */
	float fed_tax;
	float tax_rate_low = .15;		/* the percentage of the tax up to the threshold*/
	float tax_rate_high = .2;		/* the percentage of the tax over the threshold */
	float threshold = 800.0;		/* at this point the tax rate changes 		    */
	
	/* if making more than the threshold */
	if ( gross_pay > threshold )
	{
		fed_tax = threshold * tax_rate_low + (gross_pay - threshold) * tax_rate_high;
	} /* End if */
	/* within threshold */
	else
	{
		fed_tax = gross_pay * tax_rate_low;
	} /* End else */ 
	
	return fed_tax;
	
} /* End calculate_fedtax */

/* Calculate net pay (gross pay - fedtax) */
float calculate_net_pay(float gross_pay, float fedtax)
{
	/* Variable Declarations */	
	float net_pay; /* Store calculated net pay */
	
	net_pay = gross_pay - fedtax;
	
	return net_pay;
		
} /* End calculate_net_pay */


