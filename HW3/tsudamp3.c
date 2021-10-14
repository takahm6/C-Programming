/* -----------------------------------------------------------------------------
Program file: tsudamp3.c 
Author:       Makiko Tsuda
Date:         10/9/2021
Class:		  Intro to Programming with C Part 2
Assignment:   #3 
Objective:    The program prompts the user to enter some information 
			  about up to 20 individuals and store them in a structure. 
			  Checks the state code, zip code, and date,
			  Once the data has been entered, it prints out a report.	   
------------------------------------------------------------------------------*/
#include <stdio.h>
#include<string.h> 

/* Define values for the input length */
#define TITLE 30 			/* Report title length */
#define LAST 15				/* Last name length */
#define FIRST 10			/* First Name length */
#define STREET 15			/* Streed Address Length */
#define CITY 10				/* City name Length */
#define STATE 3				/* State Code Length */
#define ZIP 5				/* Zip code length */
#define MAXPPL 5			/* Max number of friends on a list */

/* Function Prototypes */
int validate_state(char[]);
int validate_zip(char[], int);
int validate_date(int, int, int);
int is_leap_year(int);
void safer_gets(char[], int);

/* Struct Definition */
struct name
{
	char last_name[LAST];
	char first_name[FIRST];
	char middle_initial;
};

struct address
{
	char street[STREET];
 	char city[CITY];
 	char state[STATE];
 	char zip[ZIP];
};

struct date
{
	int yyyy;
	int mm;
	int dd;
};

struct information
{
	struct name fullname;
	struct address addr;
	struct date sdate;
};

int main(void) 
{
	/* Variable Declarations */
	char 				report_title[TITLE];		/* For the report title */
	int 				num_people;					/* Non of people to process */	
	char				c;							/* Used to clear the buffer */ 
	int 				i;							/* Counter variable			*/
	struct information 	info[MAXPPL];				/* Hold upto 20 ppl's data */
	char				zip[ZIP];
	int 				zipok;
	
	/* Prompt for the report title */
	printf ("Welcome to Friends Program\n\n");
	printf ("Please enter Report Title (Upto 29 characters): ");
	safer_gets (report_title, TITLE); 
	
	/* Prompt for the number of record to process */
	do
	{
		printf ("How many people do you wish to process? (Enter 1 - 20): ");
		scanf("%d", &num_people);
		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
		
		/* only accept an input between 1 - 20 */
 		if( num_people < 1 || num_people > 20 )
 		{
 			printf("Please enter a value between 0 and 20.\n\n");
 		} /* End if */	
		
	} while ( num_people < 1 || num_people > 20 ); /* End while */
	
	/* Prompt to enter the personal data */
	for ( i = 0; i < num_people; i++ )
	{
 		/* Prompt user for first name. */
		printf ("\n");
 		printf ("Friend # %d : ",i+1);
		printf ("\n");
     	printf ("Enter first name: ");
     	safer_gets (info[i].fullname.first_name, FIRST);  

     	/* Prompt user for last name. */
     	printf ("Enter last name: ");
     	safer_gets (info[i].fullname.last_name, LAST);  

     	/* Prompt user for mid initial */
     	printf ("Enter middle initial: ");
		info[i].fullname.middle_initial = getchar ();
		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */ 
     	
		/* Prompt user for street address */
     	printf ("Enter street address: ");
     	safer_gets (info[i].addr.street, STREET);  
     	
		/* Prompt user for city */
     	printf ("Enter city: ");
     	safer_gets (info[i].addr.city, CITY);  
     	
		/* Prompt user for state code */
		do
		{
     		printf ("Enter state (2-letter code): ");
     		safer_gets (info[i].addr.state, STATE);  
     		
     		/* Run a validation */
     		if ( validate_state(info[i].addr.state) == 0 )
     		{
     			printf("Invalid State Code, please re-enter.\n\n");
     		} /* End if */
     		
		} while ( validate_state(info[i].addr.state) == 0 ); /* End while */
     	
  		/* Prompt user for street address */
  		do
  		{
     		printf ("Enter zip code (5 digit): ");
     		zipok = validate_zip (info[i].addr.zip, ZIP);  
			if ( zipok == 0 ) 
				printf("Please re-enter a valid zip code. \n");	
									   
		} while ( zipok == 0 ); /* End while */
		
		/* Prompt user for date */
		do
		{
     		printf ("Enter date (mm/dd/yyyy): ");
     		scanf ("%d/%d/%d", &info[i].sdate.mm, &info[i].sdate.dd, &info[i].sdate.yyyy); 
     		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
     		
     		/* validate date */
     		if ( validate_date(info[i].sdate.mm, info[i].sdate.dd, info[i].sdate.yyyy) == 0 )
     		{
     			printf("Invalid date. Please re-enter\n\n");
     		} /* End if */
     		
		} while ( validate_date(info[i].sdate.mm, info[i].sdate.dd, info[i].sdate.yyyy) == 0 ); /* End while */
     	
	}/* End for loop */
	
	/* Print the report */
	printf("\n\n");
	for ( i = 1; i < (80 - strlen(report_title))/2; i++ )
	{
 		printf(" ");/* skips half of the white space to center the report title */
	} /* End for */
	
	printf("%s\n",report_title);
		
	/* ----------------------------------------------------------------------------- */
	/* This underlines the entire title no matter how big */
	/* ----------------------------------------------------------------------------- */
	for ( i = 1; i < (80 - strlen(report_title))/2; i++ )
	{
 		printf(" "); /* skips half of the white space to center the underlining */
	} /* End for */
	
	for ( i = 1; i <= strlen(report_title); i++ ) /* prints as many dashes as the length of the title */
	{
		printf("-");
	} /* End for */
				
	printf("\n\n");	
	
	printf("Name \t\t\t\t Address \t\t Friended Date\n\n");
	
	for (i = 0; i < num_people; i++ )
	{
		printf("%s %s \t\t\t %s %.5d \t\t %d/%d/%d\n", info[i].fullname.first_name, 
				info[i].fullname.last_name,  
				info[i].addr.state, atoi(info[i].addr.zip),info[i].sdate.mm, 
				info[i].sdate.dd, info[i].sdate.yyyy);
	} /* End for */
	
	return 0;
} /* End Main */


/* This function validates a two-digit state code (US only) */
/* Return 1 if the code is valid, return 0 otherwise 		*/
int validate_state(char state_code[])
{
	/* Variable Declarations */
	int i;										
	char states[][3] = {"AL","AK","AZ","AR","CA","CO","CT","DE",
						"DC","FL","GA","HI","ID","IL","IN","IA",
						"KS","KY","LA","ME","MD","MA","MI","MN",
						"MS","MO","MT","NE","NV","NH","NJ","NM",
						"NY","NC","ND","OH","OK","OR","PA","RI",
						"SC","SD","TN","TX","UT","VT","VA","WA",
						"WV","WI","WY"};
	
	/* force it to upper case to test for a  match */
	state_code[0] = toupper(state_code[0]);
	state_code[1] = toupper(state_code[1]);
			
	for ( i = 0; i < 51; i++ )
	{
		if (strcmp(state_code, states[i]) == 0)
		{
			return 1;	/* Match found, it is valid */
		} /* End if */
	} /* End for */
	
	/* if no match, not a valid state code */
	return 0;
	
} /* End validate_state */


/* This function validates if the zip_code is zcode length */
int validate_zip(char zip_code[], int zcode)
{
	char 	ok = 1;		/* A flag, if it is 1 the zip is ok */
  	int 	i;			/* a counter */

  	/* Read name from input buffer, character by character,   */
  	/* up until the maximum number of characters in the array.*/
  	/* ------------------------------------------------------ */

  	for (i = 0; i < zcode; i++)
  	{
     	zip_code[i] = getchar();
     
	 	if(zip_code[i] == '\n')
	    	break;
	 	else
	 		if(!isdigit(zip_code[i]))
				ok = 0; 
	 
	} /* end for */
   
   	/* if shorter than 5 digit, not ok */
   	if(i < zcode) 
   		ok = 0;
   
   	if(i == zcode && zip_code[i] != '\n') 
		while (getchar() != '\n');

   	/* Ensure the last element in the array contains the null terminator. */
   	/* ------------------------------------------------------------------ */

   	zip_code[i] = '\0';

	return ok;	
		
} /* End validate_zip */


/* This function checks the entered date is a real calender date */
int validate_date (int month, int day, int year)
{
	/* Variable Declarations */
	int state = 1;			/* if valid, 1. If not 0 */
	
	/* Check if the year is a 4-digit */
	if ( year < 1000 || year > 9999 )
	{
		state = 0;
		return state;
	} /* End if */
	
	if ( month < 1 || month > 12 )
	{
		state = 0;
		return state;
	} /* End if */
	
	/* if February */
	if ( month == 2 )
	{
		/* is it a leap year ? */
		if ( is_leap_year(year) == 1 )
		{
			if ( day < 0 || day > 29 )
			{
				state = 0;
				return state;
			} /* End if */
		} /* End if */
		
		/* Regular February */
		else if ( day < 0 || day > 28 )
		{
			state = 0;
			return state;
		} /* End Else if */
	}/* End if */
	
	/* Any other month */
	else if ( month == 4 || month == 6 || month == 9 || month == 11 )
	{
		if ( day < 0 || day > 30 )
		{
			state = 0;
			return state;
		} /* End if */
	} /* End else */
	
	else 
	{
		if ( day < 0 || day > 31 )
		{
			state = 0;
			return state;
		} /* End if */
	}/* End else */
	
	return state;
} /* End of validate_date */


/* How to determine a leap year, */
int is_leap_year (int year)
{
	/* Variables Declarations */
	int leap_year = 0;			/* if leap year 1, if not 0 */
	
	/* the year is divisible by 100, and by 400
	   It is a leap year 				      */
 	if ( (year % 100 == 0 ) && (year % 400 == 0) ) 
 	{
		leap_year = 1;
		return leap_year;
 	} /* End if */
 	
 	/* When the year is not divisible by 100,
	   and divisible by 4, It is a leap year */
	else if ( (year % 100 != 0 ) && (year % 4 == 0) )
	{		
		leap_year = 1;
		return leap_year;
	} /* end else if */
	
	/* anything else, not a leap year */
	return leap_year;
		
} /* End of is_leap_year */


/* safer_gets adapted from the course resource.   */
/* Accepts a string input and make sure the input */
/* does not over flow the allocated space		  */
void safer_gets (char array[], int max_chars)
{
	/* Variable */
	int i;		/* a counter */

  	for (i = 0; i < max_chars - 1; i++)
  	{
     	array[i] = getchar();

		/* if it was a new line character, end the loop */
     	if (array[i] == '\n')
     	{
        	break;
     	} /* End if */
  
   	} /* end for */


   	if (i == max_chars - 1 )
   	{
     	if (array[i] != '\n')
     	{
       		while (getchar() != '\n');
     	} /* End if */
     
   	} /* End if */

	/* Terminate the string */
 	array[i] = '\0';

} /* end safer_gets */
