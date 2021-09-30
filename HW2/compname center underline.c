/*---------------------------------------------------------------------------
Program file:        center/underline  sample
Author:              Jim Sears
Assignment:         
Course #:            INFO 2120
Objective:      	 {Uses strlen(string) function (an enhancement)} 
				
-----------------------------------------------------------------------------*/

#include<stdio.h>
#include<string.h> 

main()
{
        int     x;
        char    c, company[] = "Fantasmic Company, Incorporated";

		printf("\n\n");
		printf ("                                Payroll Report\n");
		for(x = 1; x < (80 - strlen(company))/2; x++)
		  printf(" ");// skips half of the white space to center the company name
		printf ("%s\n",company);
 
		
	/* ----------------------------------------------------------------------------- */
	/* This underlines the entire Company Name no matter how big (extra not required)*/
	/* ----------------------------------------------------------------------------- */
 		for(x = 1; x < (80 - strlen(company))/2; x++)
		  printf(" ");// skips half of the white space to center the underlining
		for(x = 1; x <= strlen(company); x++)// prints as many dashes as the length of the company name
				printf ("-");
				
		printf ("\n\n");	  

} // end main
