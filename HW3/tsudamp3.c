/* -----------------------------------------------------------------------------
Program file: tsudamp3.c 
Author:       Makiko Tsuda
Date:         10/9/2021
Class:		  Intro to Programming with C Part 2
Assignment:   #3 
Objective:    The program prompts the user to enter some information 
			  about up to 20 individuals and store them in a structure. 
			  Input checks the state code and zip code.
			  Once the data has been entered, it prints out a report the
			  data.	   
------------------------------------------------------------------------------*/
#include <stdio.h>
#include<string.h> 

/* Define values for the input length */
#define TITLE 30
#define LAST 15
#define FIRST 10
#define STREET 15
#define CITY 10
#define STATE 3
#define ZIP 5
#define MAXPPL 5

/* Function Prototypes */
int validate_state(char[]);
int validate_zip(char[], int);
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
	struct date dd;
};

int main(void) 
{
	/* Variable Declarations */
	char 				report_title[TITLE];		/* For the report title */
	int 				num_people;				/* Non of people to process */	
	char				c;						/* Used to clear the buffer */ 
	int 				i;						/* Counter variable			*/
	struct information 	info[MAXPPL];				/* Hold upto 20 ppl's data */
	char				zip[ZIP];
	int 				zipok;
	
	/* Prompt for the report title */
	printf ("Please enter Report Title: ");
	safer_gets (report_title, TITLE); 
	
	/* Prompt for the number of record to process */
	do
	{
		printf ("How many people do you wish to process? (Enter 1 - 20): ");
		scanf("%d", &num_people);
		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
		
		/* only accept an input between 1 - 20 */
 		if( num_people < 0 || num_people > 20 )
 		{
 			printf("Please enter a value between 0 and 20.\n\n");
 		} /* End if */	
		
	} while ( num_people < 0 || num_people > 20 ); /* End while */
	
	/* Prompt to enter the personal data */
	for ( i = 0; i < num_people; i++ )
	{
 		/* Prompt user for first name. */
 		printf ("Friend # %d : ",i+1);
		printf ("\n");
     	printf ("Enter first name: ");
     	safer_gets (info[i].fullname.first_name, FIRST);  

     	/* Prompt user for last name. */
     	printf ("Enter last name: ");
     	safer_gets (info[i].fullname.last_name, LAST);  

     	/* Prompt user for mid initial */
     	printf ("Enter middle initial: ");
		scanf ("%c", &info[i].fullname.middle_initial);
		while ((c = getchar() != '\n') && c != EOF); /* clear buffer */
     	//safer_gets (info[i].fullname.middle_initial, 1);  
     	
		/* Prompt user for street address */
     	printf ("Enter street address: ");
     	safer_gets (info[i].addr.street, STREET);  
     	
		/* Prompt user for city */
     	printf ("Enter city: ");
     	safer_gets (info[i].addr.city, CITY);  
     	
		/* Prompt user for street address */
     	printf ("Enter state (2-letter code): ");
     	safer_gets (info[i].addr.state, STATE);  
     	
  		/* Prompt user for street address */
  		do
  		{
     		printf ("Enter zip code (5 digit): ");
     		zipok = validate_zip (info[i].addr.zip, ZIP);  
			if (zipok == 0) 
				printf("Please re-enter a valid zip code. \n");	
									   
		} while (zipok == 0); /* End while */
     	
	}/* End for loop */
	printf("\n");
	
	printf(report_title);
	printf("\n");
	
	for (i = 0; i < num_people; i++ )
	{
		printf("%s %s\n", info[i].fullname.first_name, info[i].fullname.last_name);
		printf("%s %s, %s %.5d\n", info[i].addr.street, info[i].addr.city, info[i].addr.state, atoi(info[i].addr.zip));
	}
	
	/* Validate the zip */
/*	do
	{
		printf ("\nEnter zip code: ");
		zipok = validate_zip(zip);
		if (zipok == 0) 
			printf("Please re-enter a valid zip code. \n");	
									   
	} while (zipok == 0);
	
	printf("good zip code was: %.5d\n", atoi(zip));		
	*/
	
	return 0;
}

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
		
}// endf


void safer_gets (char array[], int max_chars)
{

  int i;

  for (i = 0; i < max_chars - 1; i++)
  {
     array[i] = getchar();


     if (array[i] == '\n')
        break;
  
   } /* end for */


   if (i == max_chars - 1 )

     if (array[i] != '\n')
       while (getchar() != '\n');

   array[i] = '\0';
 

} /* end safer_gets */
